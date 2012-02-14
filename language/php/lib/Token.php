<?php

class Token
{
	public $type;
	public $range;
	public $text;
	
	public function is($type, $text = null)
	{
		return ($this->type == $type && (!$text || $this->text == $text));
	}
	
	public function __toString()
	{
		return "{$this->type} '{$this->text}'";
	}
}
