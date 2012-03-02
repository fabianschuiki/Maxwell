<?php

class Range
{
	public $source;
	public $start;
	public $end;
	
	public function combine(Range $r) {
		$this->start = ($this->start->offset < $r->start->offset ? $this->start : $r->start);
		$this->end   = ($this->end  ->offset > $r->end  ->offset ? $this->end   : $r->end);
	}
	
	public function contains($line, $column) {
		if ($line <  $this->start->line) return false;
		if ($line >  $this->end->line)   return false;
		if ($line == $this->start->line && $column < $this->start->column)  return false;
		if ($line == $this->end->line   && $column >= $this->end->column)   return false;
		return true;
	}
	
	public function __toString() {
		$s  = $this->start->line.'.'.$this->start->column;
		$s .= '-';
		if ($this->start->line != $this->end->line)
			$s .= $this->end->line.'.';
		$s .= $this->end->column;
		return $s;
	}
}