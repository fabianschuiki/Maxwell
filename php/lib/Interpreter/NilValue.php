<?php
namespace Interpreter;

class NilValue extends Value
{
	public function type()  { return new \LET\GenericType(); }
	public function value() { return "nil"; }
}