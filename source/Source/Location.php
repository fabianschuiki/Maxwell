<?php
namespace Source;

class Location
{
	protected $line   = 0;
	protected $column = 0;
	protected $offset = 0;
	
	public function getLine()   { return $this->line; }
	public function getColumn() { return $this->column; }
	public function getOffset() { return $this->offset; }
	
	public function addColumn()
	{
		$this->column++;
		$this->offset++;
	}
	
	public function addLine()
	{
		$this->column = 0;
		$this->line++;
		$this->offset++;
	}
	
	public function __toString()
	{
		return "{$this->line}:{$this->column}";
	}
}
