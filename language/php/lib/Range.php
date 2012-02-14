<?php

class Range
{
	public $start;
	public $end;
	
	public function combine(Range $r) {
		$this->start = ($this->start->offset < $r->start->offset ? $this->start : $r->start);
		$this->end   = ($this->end  ->offset > $r->end  ->offset ? $this->end   : $r->end);
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
