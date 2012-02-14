<?php

class TokenScanner
{
	public $tokens;
	private $index;
	
	public function __construct(&$tokens) {
		$this->tokens = $tokens;
		$this->index = 0;
	}
	
	public function done() {
		
	}
}
