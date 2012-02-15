<?php

class Node
{
	public $kind;
	
	public function is($k) {
		return strpos($this->kind, $k) === 0;
	}
}
