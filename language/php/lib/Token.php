<?php

class Token
{
	public $type;
	public $range;
	public $text;
	
	public function is($type) {
		return $this->type == $type;
	}
}
