<?php
namespace Interpreter;

class Interpreter
{
	public $root;
	public $scope;
	public $issues;
	
	public function evaluate(\LET\Expr $node, $scope = null)
	{
		if (!$this->scope && $this->root) $this->scope = new Scope($this->root->scope);
		if (!$scope) $scope = $this->scope;
		assert($scope instanceof Scope);
		
		echo "evaluating {$node->desc()}\n";
		$class = get_class($node);
		do {
			$func = 'evaluate'.str_replace('LET\\', '', $class);
			//echo "trying $func\n";
			$subscope = $scope;
			if (isset($node->subscope)) $subscope = new Scope($node->subscope, $scope);
			if (method_exists($this, $func)) {
				return call_user_func_array(array($this, $func), array($subscope, $node));
			}
			$class = get_parent_class($class);
		} while ($class);
		
		$this->issues[] = new \Issue(
			'error',
			"Don't know how to interpret {$node->desc()}.",
			$node
		);
		return null;
	}
	
	private function evaluateCall(Scope $scope, \LET\Call $call)
	{
		$func = $call->func();
		if (!$func) {
			$this->issues[] = new \Issue(
				'error',
				"Call is not bound to a function.",
				$call
			);
			return null;
		}
		
		$args  = array();
		$pairs = \LET\TypeTuple::fieldPairs($call->args()->unconstrainedType(), $func->type()->in());
		foreach ($call->args()->fields() as $name => $expr) {
			$result = $this->evaluate($expr, $scope);
			assert($result);
			if (!$result) return null;
			$args[$pairs[$name]] = $result;
		}
		
		if ($func instanceof \LET\BuiltinBinaryOp) {
			$result = null;
			$a = array_shift($args);
			$b = array_shift($args);
			switch ($func->name()) {
				case '+': $result = ($a->value() + $b->value()); break;
				case '-': $result = ($a->value() - $b->value()); break;
				case '*': $result = ($a->value() * $b->value()); break;
				case '/': $result = ($a->value() / $b->value()); break;
				case '=': $a->set($b); $result = $a->value(); break;
			}
			if ($result === null) {
				$this->issues[] = new \Issue(
					'error',
					"Unable to calculate result of {$call->desc()}.",
					$call
				);
				return null;
			}
			return new ConcreteValue($a->type(), $result);
		}
		
		if ($func instanceof \LET\Func) {
			return $this->evaluateFunc($scope, $func, $args);
		}
		
		$this->issues[] = new \Issue(
			'error',
			"Don't know how to call function.",
			$func
		);
		return null;
	}
	
	private function evaluateConstant(Scope $scope, \LET\Constant $const)
	{
		return new ConcreteValue($const->type(), $const->value());
	}
	
	private function evaluateFunc(Scope $scope, \LET\Func $func, array $args)
	{
		$subscope = new Scope($func->subscope, $scope);
		
		foreach ($func->inputs()  as $arg) $subscope->vars[$arg->name()] = new Variable($arg, $args[$arg->name()]);
		foreach ($func->outputs() as $arg) $subscope->vars[$arg->name()] = new Variable($arg);
		
		$this->evaluateStmts($subscope, $func->stmts());
		
		$result = new TupleValue;
		foreach ($func->outputs() as $arg) $result->fields[$arg->name()] = $subscope->vars[$arg->name()];
		if (count($result->fields) == 1) return array_shift($result->fields);
		return $result;
	}
	
	private function evaluateStmts(Scope $scope, array $stmts)
	{
		foreach ($stmts as $stmt) $this->evaluate($stmt, $scope);
	}
	
	private function evaluateIdent(Scope $scope, \LET\Ident $ident)
	{
		$definedIn = $scope;
		while ($definedIn && $ident->boundTo->scope !== $definedIn->let) {
			$definedIn = $definedIn->outer;
		}
		assert($definedIn instanceof Scope);
		
		return $definedIn->vars[$ident->boundTo->name()];
	}
}