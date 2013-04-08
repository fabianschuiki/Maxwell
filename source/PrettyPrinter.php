<?php
/* Copyright © 2013 Fabian Schuiki */

class PrettyPrinter
{
	protected $repository;

	public function __construct(Repository $repo)
	{
		$this->repository = $repo;
	}

	static private function indent($s)
	{
		return "    ".str_replace("\n", "\n    ", $s);
	}

	static private function precedenceWrap($s, &$context, $precedence)
	{
		if (!isset($context["precedence"]))
			return $s;
		$outer = $context["precedence"];
		if (!$outer || $outer <= $precedence)
			return $s;
		return "($s)";
	}

	static private function ctxget(&$context, $path)
	{
		$obj = $context;
		foreach (explode("/", $path) as $index) {
			if (!isset($obj[$index]))
				return null;
			$obj = $obj[$index];
		}
		return $obj;
	}

	/**
	 * Returns a string containing valid Maxwell code for the given root object
	 * ID.
	 */
	public function formatRootObject($objectId, &$context = null)
	{
		$object = $this->repository->getObject($objectId);
		return $this->formatObject($object, $context);
	}

	public function formatObject(RepositoryObject $object, &$context = null)
	{
		$funcName = "format".$object->getClass();
		if (method_exists($this, $funcName)) {
			if ($object instanceof \Objects\CallInterface && static::ctxget($context, "annotate/selected-call") === true) {
				$c = $object->getSelectedCallCandidate(false);
				if ($c) {
					$context["annotations"][] = "{$object->getCallName()} calls {$c->getFunc()->getId()}";
				}
			}
			if ($object instanceof \Objects\TypeInterface) {
				if (static::ctxget($context, "annotate/types") === true) {
					$at = $object->getActualType(false);
					if ($at) {
						$context["annotations"][] = "type of {$object->getId()} = ".\Type::describe($at);
					}
				}
			}
			return $this->$funcName($object, $context);
		}
		throw new \InvalidArgumentException("Don't know how to pretty-print {$object->getClass()}.");
	}

	public function formatFunctionDefinition($object, &$context)
	{
		$inputs = array();
		$outputs = array();
		$stmts = array();

		foreach ($object->getInputs()->getArguments()->getElements() as $arg) {
			$inputs[] = $this->formatObject($arg, $context);
		}
		foreach ($object->getOutputs()->getArguments()->getElements() as $arg) {
			$outputs[] = $this->formatObject($arg, $context);
		}

		foreach ($object->getBody()->getStmts()->getElements() as $stmt) {
			unset($context["annotations"]);
			$stmts[] = $this->formatObject($stmt, $context);
			$ans = static::ctxget($context, "annotations");
			unset($context["annotations"]);
			if ($ans) {
				foreach ($ans as $an) {
					$anmod = str_replace($object->getId().".", "", $an);
					$stmts[] = "// ".str_replace("\n", "\n// ", $anmod);
				}
			}
		}

		$s = "func {$object->getName()}";
		if ($inputs) $s .= " (".implode(", ", $inputs).")";
		if ($outputs) $s .= " -> (".implode(", ", $outputs).")";
		$s .= "\n{\n";
		foreach ($stmts as $stmt) $s .= static::indent($stmt)."\n";
		$s .= "}";
		return $s;
	}

	public function formatFunctionArgument($object, &$context)
	{
		return $this->formatObject($object->getTypeExpr(), $context)." ".$object->getName();
	}

	public function formatExprStmt($object, &$context)
	{
		//unset($context["annotations"]);
		$s = $this->formatObject($object->getExpr(), $context).";";
		/*$ans = static::ctxget($context, "annotations");
		unset($context["annotations"]);
		if ($ans) {
			foreach ($ans as $an) {
				$anmod = str_replace($object->getId().".", "", $an);
				$s .= "\n// ".str_replace("\n", "\n// ", $anmod);
			}
		}*/
		return $s;
	}

	public function formatAssignmentExpr($object, &$context)
	{
		$precedence = 0;
		$s  = $this->formatObject($object->getLhs(), $context);
		$s .= " = ";
		$s .= $this->formatObject($object->getRhs(), $context);
		return static::precedenceWrap($s, $context, $precedence);
	}

	public function formatBinaryOperatorExpr($object, &$context)
	{
		$precedence = 1;
		if (in_array($object->getOperator(), array("*", "/")))
			$precedence = 2;
		$s  = $this->formatObject($object->getLhs(), $context);
		$s .= " ".$object->getOperator()." ";
		$s .= $this->formatObject($object->getRhs(), $context);
		return static::precedenceWrap($s, $context, $precedence);
	}

	public function formatIdentifierExpr($object, &$context)
	{
		if (static::ctxget($context, "annotate/bindings") === true) {
			$t = $object->getBindingTarget(false);
			if ($t) {
				$context["annotations"][] = $object->getName()." -> ".$t->getId();
			}
		}
		return $object->getName();
	}

	public function formatConstantExpr($object, &$context)
	{
		return $object->getValue();
	}

	public function formatTypeExpr($object, &$context)
	{
		return $this->formatObject($object->getExpr(), $context);
	}

	public function formatCallExpr($object, &$context)
	{
		$args = array();
		foreach ($object->getArguments()->getElements() as $arg) {
			$args[] = $this->formatObject($arg, $context);
		}
		return $object->getName()."(".implode(", ", $args).")";
	}

	public function formatVariableDefinitionExpr($object, &$context)
	{
		$s = "var ".$object->getName();
		$t = $object->getTypeExpr();
		if (!$t instanceof \Objects\NullObject) {
			$s .= " ".$this->formatObject($t, $context);
		}
		$i = $object->getInitialExpr();
		if (!$i instanceof \Objects\NullObject) {
			$s .= " = ".$this->formatObject($i, $context);
		}
		return $s;
	}

	public function formatUnionTypeExpr($object, &$context)
	{
		$a = array();
		foreach ($object->getTypeExprs()->getElements() as $te) {
			$a[] = $this->formatObject($te, $context);
		}
		return implode("|", $a);
	}

	public function formatAssumeStmt($object, &$context)
	{
		return "assume ".$this->formatObject($object->getTarget(), $context)." = ".$this->formatObject($object->getAssumption(), $context).";";
	}

	public function formatAssumption($object, &$context)
	{
		return $this->formatObject($object->getTarget(), $context)." = ".$this->formatObject($object->getAssumption(), $context);
	}

	public function formatTypeDefinition($object, &$context)
	{
		$a = array();
		foreach ($object->getTypes()->getElements() as $t) {
			$a[] = $this->formatObject($t, $context);
		}
		return "type {$object->getName()} ".implode(", ", $a);
	}

	public function formatStructureType($object, &$context)
	{
		$body = "";
		foreach ($object->getInherits()->getElements() as $e) {
			$body .= "\ninherit {$e->getType()->getName()}";
			if ($n = $e->getName(false)) {
				$body .= " $n";
			}
			$body .= ";";
		}
		foreach ($object->getFields()->getElements() as $f) {
			$body .= "\n".$f->getName()." ".$this->formatObject($f->getType(), $context).";";
		}
		return "struct {".static::indent($body)."\n}";
	}

	public function formatNamedType($object, &$context)
	{
		return $object->getName();
	}
}