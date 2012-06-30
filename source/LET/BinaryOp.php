<?php
namespace LET;

abstract class BinaryOp extends Call
{
	//public function kind() { return 'Call'; }
	public function nice() { return "Binary Operator {$this->callee()->name()}"; }
}