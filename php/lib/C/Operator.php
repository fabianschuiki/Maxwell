<?php
namespace C;

class Operator extends Expr
{
	public $operator;
	public $lhs;
	public $rhs;
	
	public function __construct($operator, $lhs = null, $rhs = null)
	{
		parent::__construct();
		$this->operator = $operator;
		$this->lhs = $lhs;
		$this->rhs = $rhs;
	}
	
	public function getExpr()
	{
		$lhs = $this->lhs->getExpr();
		$rhs = $this->rhs->getExpr();
		
		$p = $this->getPrecedence();
		if ($lhs instanceof Operator && $lhs->getPrecedence() < $p) $lhs = "($lhs)";
		if ($rhs instanceof Operator && $rhs->getPrecedence() < $p) $rhs = "($rhs)";
		
		return "$lhs {$this->operator} $rhs";
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