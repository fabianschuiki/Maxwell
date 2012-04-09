<?php
namespace Interpreter;

class NilValue extends Value
{
	public function type()  { return new GenericType(); }
	public function value() { return "nil"; }
}