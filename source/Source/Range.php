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
			else
				assert($file === $r->getFile());
		}
		
		if (!$file || !$ls || !$le) return null;
		return new Range($file, clone $ls, clone $le);
	}
}
