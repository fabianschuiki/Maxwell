<?php
namespace Interpreter;

class Scope
{
	public $let;
	public $outer;
	public $vars;
	
	public function __construct(\LET\Scope $let, $outer = null)
	{
		assert(!$outer || $outer instanceof Scope);
		
		$this->let   = $let;
		$this->outer = $outer;
		$this->vars  = array();
	}
	
	public function get($name)
	{
		assert(is_string($name));
		if (isset($this->vars[$name])) return $this->vars[$name];
		
		$node = array_shift($this->let->find($name));
		if (!$node) return null;
		
		$value = new ObjectValue($node->type());
		$this->vars[$name] = $value;
		return $value;
	}
}