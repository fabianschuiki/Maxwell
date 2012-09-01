<?php
namespace AST;

abstract class Node
{
	protected $id;
	
	public function __construct()
	{
		$this->id = \IDProvider::makeID();
	}
	
	public function getID() { return $this->id; }
	
	public function getRange()
	{
		$ranges = array();
		foreach ($this as $key => $value) {
			if (method_exists($value, "getRange"))
				$ranges[] = $value->getRange();
		}
		return call_user_func_array(array("\Source\Range", "union"), $ranges);
	}
}