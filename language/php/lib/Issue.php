<?php

class Issue
{
	public $type;
	public $message;
	public $range;
	public $marked;
	
	public function __construct($type, $message, Range $range, $marked = null)
	{
		$this->type    = $type;
		$this->message = $message;
		$this->range   = $range;
		$this->marked  = $marked;
	}
	
	public function __toString()
	{
		if (!is_array($this->marked)) {
			$this->marked = array();
		}
		
		$sfr  = basename($this->range->source->path);
		$sfr .= ':';
		$sfr .= $this->range->start->line.':'.$this->range->start->column;
		
		$t = $this->type.':';
		if ($this->type == 'error')   $t = "\033[1;31m$t\033[0m";
		if ($this->type == 'warning') $t = "\033[1;33m$t\033[0m";
		
		$ml = "$sfr: $t {$this->message}";
		$o  = $ml;
		
		$lines = range($this->range->start->line, $this->range->end->line);
		foreach ($this->marked as $r) {
			$lines = array_merge($lines, range($r->start->line, $r->end->line));
		}
		$lines = array_unique($lines);
		sort($lines);
		
		$ls = explode("\n", $this->range->source->content);
		$pl = $lines[0]-1;
		$o .= "";
		foreach ($lines as $l) {
			if ($l != $pl+1) {
				$o .= "...\n";
			}
			$pl = $l;
			$line = str_replace("\t", " ", $ls[$l-1]);
			$marks = '';
			for ($i = 0; $i < strlen($line); $i++) {
				$mark = ($line[$i] == "\t" ? "\t" : " ");
				if ($this->range->contains($l, $i+1)) {
					$mark = '^';
				} else {
					foreach ($this->marked as $r) {
						if ($r->contains($l, $i+1)) {
							$mark = '~';
							break;
						}
					}
				}
				$marks .= $mark;
			}
			
			$prefix = sprintf('%4d: ', $l);
			$pad = str_repeat(' ', strlen($prefix));
			$o .= "\n";
			$o .= "$prefix$line\n";
			$o .= "$pad\033[0;36m".$marks."\033[0m";
		}
		
		return $o;
	}
}
