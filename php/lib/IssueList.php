<?php

class IssueList implements ArrayAccess
{
	public $issues = array();
	public $num_warnings = 0;
	public $num_errors   = 0;
	
	public function add(Issue $i)
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
		exit(-1);
	}
	
	public function dump()
	{
		foreach ($this->issues as $i) {
			echo "$i\n";
		}
	}
}