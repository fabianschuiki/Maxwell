<?php
namespace Interpreter;

class Interpreter
{
	public $root;
	public $issues;
	
	public function evaluate(\LET\Expr $node)
	{
		echo "evaluating {$node->desc()}\n";
		$class = get_class($node);
		do {
			$func = 'evaluate'.str_replace('LET\\', '', $class);
			//echo "trying $func\n";
			if (method_exists($this, $func)) {
				return call_user_func_array(array($this, $func), array($node));
			}
			$class = get_parent_class($class);
		} while ($class/* != 'LET\Node'*/);
		
		$this->issues[] = new \Issue(
			'error',
			"Don't know how to interpret {$node->desc()}.",
			$node
		);
		return null;
	}
	
	private function evaluateCall(\LET\Call $call)
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
			$result = $this->evaluate($expr);
			if (!$result) return null;
			$args[$pairs[$name]] = $result;
		}
		
		if ($func instanceof \LET\BuiltinBinaryOp) {
			$result = null;
			$a = array_shift($args);
			$b = array_shift($args);
			switch ($func->name()) {
				case '+': $result = ($a->value + $b->value); break;
				case '-': $result = ($a->value - $b->value); break;
				case '*': $result = ($a->value * $b->value); break;
				case '/': $result = ($a->value / $b->value); break;
			}
			if ($result === null) {
				$this->issues[] = new \Issue(
					'error',
					"Unable to calculate result of {$call->desc()}.",
					$call
				);
				return null;
			}
			return new Value($a->type, $result);
		}
		
		if ($func instanceof \LET\Func) {
			return $this->evaluateFunc($func, $args);
		}
		
		$this->issues[] = new \Issue(
			'error',
			"Don't know how to call function.",
			$func
		);
		return null;
	}
	
	private function evaluateConstant(\LET\Constant $const)
	{
		return new Value($const->type(), $const->value());
	}
	
	private function evaluateFunc(\LET\Func $func, array $args)
	{
		$vars = $args;
		
		foreach ($func->stmts() as $stmt) {
			echo "stmt: {$stmt->desc()}\n";
		}
		return null;
	}
}