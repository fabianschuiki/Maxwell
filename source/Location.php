<?php

class Location
{
	public $line   = 1;
	public $column = 0;
	public $offset = 0;
	
	public function __toString()
	{
		return "{$this->line}:{$this->column}";
	}
}
