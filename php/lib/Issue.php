<?php

class Issue
{
	public $type;
	public $message;
	public $range;
	public $marked;
	
	public function __construct($type, $message, $range = null, $marked = null)
	{
		$this->type    = $type;
		$this->message = $message;
		
		if (is_array($range)) {
			$total = null;
			foreach ($range as $r) {
				if (!$r instanceof Range && method_exists($r, 'range')) $r = $r->range();
				if (!$total) {
					$total = clone $r;
				} else {
					$total->combine($r);
				} 
			}
			$range = $total;
		}
		if (!$range instanceof Range && method_exists($range, 'range')) {
			$range = $range->range();
		}
		
		if (!is_array($marked)) {
			$marked = array($marked);
		}
		$marked = array_map(function($r){
			if (!$r instanceof Range && method_exists($r, 'range')) $r = $r->range();
			return $r;
		}, $marked);
		$mb = count($marked);
		$marked = array_filter($marked, function($r){ return $r instanceof Range; });
		
		$this->range   = $range;
		$this->marked  = $marked;
	}
	
	public function __toString()
	{
		if (!is_array($this->marked)) {
			$this->marked = array();
		}
		
		$source = null;
		if ($this->range) {
			$source = $this->range->source;
		} else if (count($this->marked) > 0) {
			$source = $this->marked[0]->source;
		}
		
		$t = $this->type.':';
		if ($this->type == 'error')   $t = "\033[1;31m$t\033[0m";
		if ($this->type == 'warning') $t = "\033[1;33m$t\033[0m";
		
		$msg = str_replace("\n", "\n    : ", $this->message);
		$o = "$t $msg";
		if ($source) {
			$sfr  = basename($source->path);
			if ($this->range) {
				$sfr .= ':';
				$sfr .= $this->range->start->line.':'.$this->range->start->column;
			}
			$o = "$sfr: $o";
		}
		
		$lines = ($this->range ? range($this->range->start->line, $this->range->end->line) : array());
		foreach ($this->marked as $r) {
			if (!$source) $source = $r->source;
			$lines = array_merge($lines, range($r->start->line, $r->end->line));
		}
		$lines = array_unique($lines);
		sort($lines);
		
		if (count($lines) > 0) {
			$ls = explode("\n", $source->content);
			
			$whitelead_min = null;
			foreach ($lines as $l) {
				preg_match('/^\s*/', $ls[$l-1], $match);
				$whitelead = strlen(str_replace("\t", "    ", $match[0]));
				if (!$whitelead_min || $whitelead < $whitelead_min) $whitelead_min = $whitelead;
			}
			if (!$whitelead_min) $whitelead_min = 0;
			
			$pl = $lines[0]-1;
			$o .= "";
			foreach ($lines as $l) {
				$skipped = ($l != $pl+1);
				if ($skipped) $o .= "\r    ~";
				
				$pl = $l;
				$line = $ls[$l-1];
				$marks = '';
				for ($i = 0; $i < strlen($line); $i++) {
					$mark = ($line[$i] == "\t" ? "\t" : " ");
					if ($this->range && $this->range->contains($l, $i)) {
						$mark = '^';
					} else {
						foreach ($this->marked as $r) {
							if ($r->contains($l, $i)) {
								$mark = '~';
								break;
							}
						}
					}
					$marks .= $mark;
				}
				$line  = substr(str_replace("\t", "    ", $line),  $whitelead_min);
				$marks = substr(str_replace("\t", "    ", $marks), $whitelead_min);
			
				$prefix = sprintf('%4d', $l);
				$pad = str_repeat(' ', strlen($prefix));
				$o .= "\n";
				$o .= "$prefix| $line\n";
				$o .= "$pad| \033[0;36m".$marks."\033[0m";
			}
		}
		
		return $o;
	}
}
