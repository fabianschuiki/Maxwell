<?php
namespace Parser\AST;
require_once __DIR__.'/helper.php';

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

class FunctionStmt extends Statement
{
	public $name;
	public $function;
	public function desc($indent = 0) {
		$s = "\033[1;33m".$this->name->text."\033[0m ";
		$s .= $this->function->desc($indent);
		return $s;
	}
}

class ReturnStmt extends Statement
{
	public $keyword;
	public $expr;
	public function desc() {
		return keyword('return').' '.$this->expr->desc().';';
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

class AnonymousFunctionExpr extends Expression
{
	public $inputs;
	public $outputs;
	public $body;
	public function desc($indent = 0) {
		$s = '';
		if (count($this->inputs)) {
			$s .= '('.implode(', ', $this->inputs).') ';
		}
		if (count($this->outputs)) {
			$s .= '=> ';
			$s .= '('.implode(', ', $this->outputs).') ';
		}
		$s .= $this->body->desc($indent);
		return $s;
	}
}

class FunctionArgumentExpr extends VariableExpr
{
}
