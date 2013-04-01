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

	static private function precedenceWrap($s, $context, $precedence)
	{
		$outer = @$context["precedence"];
		if (!$outer || $outer <= $precedence)
			return $s;
		return "($s)";
	}

	/**
	 * Returns a string containing valid Maxwell code for the given root object
	 * ID.
	 */
	public function formatRootObject($objectId)
	{
		$object = $this->repository->getObject($objectId);
		return $this->formatObject($object);
	}

	public function formatObject(RepositoryObject $object, $context = null)
	{
		$funcName = "format".$object->getClass();
		if (method_exists($this, $funcName)) {
			return $this->$funcName($object, $context);
		}
		throw new \InvalidArgumentException("Don't know how to pretty-print {$object->getClass()}.");
	}

	public function formatFunctionDefinition($object, $context)
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
			$stmts[] = $this->formatObject($stmt, $context);
		}

		$s = "func {$object->getName()}";
		if ($inputs) $s .= " (".implode(", ", $inputs).")";
		if ($outputs) $s .= " -> (".implode(", ", $outputs).")";
		$s .= "\n{\n";
		foreach ($stmts as $stmt) $s .= static::indent($stmt)."\n";
		$s .= "}";
		return $s;
	}

	public function formatFunctionArgument($object, $context)
	{
		return $this->formatObject($object->getTypeExpr(), $context)." ".$object->getName();
	}

	public function formatExprStmt($object, $context)
	{
		return $this->formatObject($object->getExpr(), $context).";";
	}

	public function formatAssignmentExpr($object, $context)
	{
		$precedence = 0;
		$s  = $this->formatObject($object->getLhs(), $context);
		$s .= " = ";
		$s .= $this->formatObject($object->getRhs(), $context);
		return static::precedenceWrap($s, $context, $precedence);
	}

	public function formatBinaryOperatorExpr($object, $context)
	{
		$precedence = 1;
		if (in_array($object->getOperator(), array("*", "/")))
			$precedence = 2;
		$s  = $this->formatObject($object->getLhs(), $context);
		$s .= " ".$object->getOperator()." ";
		$s .= $this->formatObject($object->getRhs(), $context);
		return static::precedenceWrap($s, $context, $precedence);
	}

	public function formatIdentifierExpr($object, $context)
	{
		return $object->getName();
	}

	public function formatConstantExpr($object, $context)
	{
		return $object->getValue();
	}

	public function formatTypeExpr($object, $context)
	{
		return $this->formatObject($object->getExpr(), $context);
	}
}