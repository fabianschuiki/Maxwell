<?php
namespace Parser\AST;

class Block
{
	public $statements = array();
	public function desc($indent = 0) {
		$in = str_repeat('    ', $indent);
		$s = '{';
		foreach ($this->statements as $stmt) {
			$s .= "\n".$in.'    '.$stmt->desc($indent + 1);
		}
		$s .= "\n".$in.'}';
		return $s;
	}
}

class Statement
{
}

class ExpressionStmt extends Statement
{
	public $expr;
	public function desc() {
		return $this->expr->desc().';';
	}
}

class Expression
{
	public function __toString() { $s = $this->desc(); return is_string($s) ? $s : '?'; }
}

class NumericExpr extends Expression
{
	public $value;
	public function desc() {
		return numeric($this->value);
	}
}

class StringExpr extends Expression
{
	public $value;
	public function desc() {
		return string($this->value);
	}
}

class VariableExpr extends Expression
{
	public $name;
	public $type;
	public function desc() {
		$s = $this->name->text;
		if ($this->type)
			$s .= ' '.typename($this->type);
		return $s;
	}
}

class BinaryOperatorExpr extends Expression
{
	public $operator;
	public $lhs;
	public $rhs;
	public function desc() {
		$left = $this->lhs;
		$right = $this->rhs;
		if ($left  instanceof BinaryOperatorExpr) $left  = "($left)";
		if ($right instanceof BinaryOperatorExpr) $right = "($right)";
		return $left.' '.$this->operator->text.' '.$right;
	}
}


/**
 * Helper Functions
 */
function typename($token) {
	return "\033[0;31m".$token->text."\033[0m";
}
function numeric($token) {
	return "\033[0;36m".$token->text."\033[0m";
}
function string($token) {
	return "\033[0;33m\"".$token->text."\"\033[0m";
}
