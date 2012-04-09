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
	
	
}