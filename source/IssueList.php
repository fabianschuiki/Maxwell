<?php

class IssueList implements ArrayAccess
{
	static $stack = array();
	
	static public function add($type, $message, $range = null, $marked = null)
	{
		assert(count(static::$stack) > 0);
		$list = static::$stack[count(static::$stack)-1];
		
		$i = new Issue($type, $message, $range, $marked);
		$list->addIssue($i);
	}
	
	protected $issues = array();
	protected $num_warnings = 0;
	protected $num_errors   = 0;
	
	public function push()
	{
		array_push(static::$stack, $this);
	}
	
	public function pop()
	{
		$popped = array_pop(static::$stack);
		assert($popped === $this);
	}
	
	public function report()
	{
		$this->dump();
	}
	
	public function reportAndExitIfFatal()
	{
		$this->exitIfFatal();
	}
	
	//OLD INTERFACE THAT IS NOW DEPRECATED
	public function addIssue(Issue $i)
	{
		$this->issues[] = $i;
		if ($i->type == 'warning') $this->num_warnings++;
		if ($i->type == 'error')   $this->num_errors++;
	}
	
	public function offsetSet($o, $v)
	{
		assert($o === null);
		$this->add($v);
	}
	
	public function offsetExists($o) { return false; }
	public function offsetUnset($o)  {}
	public function offsetGet($o)    { return null; }
	
	public function isFatal()
	{
		return $this->num_errors > 0;
	}
	
	public function exitIfFatal()
	{
		if (!$this->isFatal()) return;
		$this->dump();
		exit(1);
	}
	
	public function dump()
	{
		foreach ($this->issues as $i) {
			echo "$i\n";
		}
		$this->issues = array();
	}
	
	public function dumpAndCheck()
	{
		$this->dump();
		return $this->isFatal();
	}
}