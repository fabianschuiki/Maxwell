<?php

class Range
{
	public $source;
	public $start;
	public $end;
	
	static public function builtin()
	{
		$r = new Range;
		$r->source = 'builtin';
		return $r;
	}
	
	public function combine(Range $r) {
		/*if ($this->start instanceof Location && $this->end instanceof Location && $r->start instanceof Location && $r->end instanceof Location) {*/
			$this->start = ($this->start->offset < $r->start->offset ? $this->start : $r->start);
			$this->end   = ($this->end  ->offset > $r->end  ->offset ? $this->end   : $r->end);
		//}
	}
	
	public function contains($line, $column) {
		if ($this->builtin || $r->builtin)
			return false;
		if ($line <  $this->start->line) return false;
		if ($line >  $this->end->line)   return false;
		if ($line == $this->start->line && $column < $this->start->column)  return false;
		if ($line == $this->end->line   && $column >= $this->end->column)   return false;
		return true;
	}
}
