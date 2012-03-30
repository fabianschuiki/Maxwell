<?php

class Range
{
	public $source;
	public $start;
	public $end;
	
	static public function union($ranges)
	{
		$range = null;
		$args = (is_array($ranges) ? $ranges : func_get_args());
		foreach ($args as $r) {
			if (!$r instanceof Range && is_object($r) && method_exists($r, 'range')) {
				$r = $r->range();
			}
			if ($r instanceof Range) {
				if (!$range) {
					$range = clone $r;
				} else {
					$range->combine($r);
				}
			}
		}
		return $range;
	}
	
	static public function builtin()
	{
		$r = new Range;
		$r->source = 'builtin';
		return $r;
	}
	
	public function combine($r) {
		if (!$r instanceof Range) return;
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
