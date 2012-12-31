<?php
namespace Source;

class Range
{
	protected $file;
	protected $start;
	protected $end;
	
	public function __construct(File $file, Location $start, Location $end)
	{
		$this->file = $file;
		$this->start = clone $start;
		$this->end = clone $end;
	}
	
	public function getFile()  { return $this->file; }
	public function getStart() { return $this->start; }
	public function getEnd()   { return $this->end; }
	
	public function getPosition() { return $this->start->getOffset(); }
	public function getLength() { return $this->end->getOffset() - $this->start->getOffset(); }
	
	public function contains($line, $column)
	{
		if ($line <  $this->start->getLine()) return false;
		if ($line >  $this->end->getLine())   return false;
		if ($line == $this->start->getLine() && $column < $this->start->getColumn()) return false;
		if ($line == $this->end->getLine()   && $column >= $this->end->getColumn())  return false;
		return true;
	}
	
	public function toString()
	{
		$loc2str = function(Location $l) { return "{$l->getOffset()}:{$l->getLine()}:{$l->getColumn()}"; };
		return $loc2str($this->start)."-".$loc2str($this->end);
	}
	
	static public function fromString($str, File $file)
	{
		$str2loc = function($s) {
			$c = explode(":", $s);
			assert(count($c) == 3);
			return Location::make($c[1], $c[2], $c[0]);
		};
		list($s,$e) = explode("-", $str);
		return new self($file, $str2loc($s), $str2loc($e));
	}
	
	static public function union($ranges)
	{
		$file = null;
		$ls = null;
		$le = null;
		
		$args = (is_array($ranges) ? $ranges : func_get_args());
		foreach ($args as $r) {
			assert($r instanceof Range);
			if ($ls === null || $r->getStart()->getOffset() < $ls->getOffset())
				$ls = $r->getStart();
			if ($le === null || $r->getEnd()->getOffset() > $le->getOffset())
				$le = $r->getEnd();
			if ($file === null)
				$file = $r->getFile();
			else if ($file !== $r->getFile())
				throw new \exception("Trying to union ranges of different files");
		}
		
		if (!$file || !$ls || !$le) return null;
		return new Range($file, clone $ls, clone $le);
	}
}
