<?php
namespace LET;

abstract class UnaryOp extends Call
{
	public function nice() { return "Unary Operator {$this->callee()->name()}"; }
}