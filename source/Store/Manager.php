<?php
namespace Store;

class Manager
{
	//Stacking mechanism
	static $stack = array();
	
	static public function get()
	{
		assert(count(static::$stack) > 0);
		return static::$stack[count(static::$stack)-1];
	}
	
	public function push()
	{
		array_push(static::$stack, $this);
	}
	
	public function pop()
	{
		$popped = array_pop(static::$stack);
		assert($popped === $this);
	}
	
	
	//Instance
	protected $dir;
	protected $tokenStore;
	protected $astStore;
	protected $letStore;
	
	public function __construct($dir)
	{
		$this->dir = $dir;
	}
	
	public function getDirectory() { return $this->dir; }
	
	public function getTokenStore()
	{
		if (!$this->tokenStore)
			$this->tokenStore = new TokenStore($this);
		return $this->tokenStore;
	}
	
	public function getASTStore()
	{
		if (!$this->astStore)
			$this->astStore = new ASTStore($this);
		return $this->astStore;
	}
	
	public function getLETStore()
	{
		if (!$this->letStore)
			$this->letStore = new LETStore($this);
		return $this->letStore;
	}
}