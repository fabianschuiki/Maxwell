<?php

class Token
{
	public $type;
	public $range;
	public $text;
	
	static public function builtin($type, $text)
	{
		$t = new Token;
		$t->type = $type;
		$t->text = $text;
		$t->range = Range::builtin();
		return $t;
	}
	
	public function is($type, $text = null)
	{
		return ($this->type == $type && (!$text || $this->text == $text));
	}
	
	public function __toString()
	{
		return $this->text;
	}
	
	public function range() { return $this->range; }
}
