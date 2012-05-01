<?php
namespace C;

class Operator extends Expr
{
	public $operator;
	public $args;
	
	public function __construct($operator, $args = null)
	{
		parent::__construct();
		$this->operator = $operator;
		$this->args = $args;
	}
	
	public function getExpr()
	{
		if (count($this->args) == 1) {
			$expr = $this->args[0]->getExpr();
			$p = $this->getPrecedence();
			if ($expr instanceof Operator && $expr->getPrecedence() < $p) $expr = "($expr)";
			return "{$this->operator}$expr";
		} else {
			$lhs = $this->args[0]->getExpr();
			$rhs = $this->args[1]->getExpr();
			
			$p = $this->getPrecedence();
			if ($lhs instanceof Operator && $lhs->getPrecedence() < $p) $lhs = "($lhs)";
			if ($rhs instanceof Operator && $rhs->getPrecedence() < $p) $rhs = "($rhs)";
			
			return "$lhs {$this->operator} $rhs";
		}
	}
	
	public function getPrecedence()
	{
		$prec = array(
			array('='),
			array('+', '-'),
			array('*', '/'),
		);
		foreach ($prec as $i => $s) if (in_array($this->operator, $s)) return $i;
		return -1;
	}
}