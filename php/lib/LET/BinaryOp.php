<?php
namespace LET;

abstract class BinaryOp extends Call
{
	public function kind() { return 'Call'; }
}