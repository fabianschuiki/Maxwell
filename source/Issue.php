<?php
use Source\Range;

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
			$ranges = array();
			foreach ($range as $r) {
				if (!$r instanceof Range && method_exists($r, 'getRange')) $r = $r->getRange();
				if (!$r instanceof Range)
					trigger_error(vartype($r)." passed as range is neither a Range nor does it implement the getRange() function", E_USER_ERROR);
				$ranges[] = $r;
			}
			$range = Range::union($ranges);
		}
		if (!$range instanceof Range && method_exists($range, 'getRange')) {
			$range = $range->getRange();
		}
		
		if (!is_array($marked)) {
			$marked = ($marked != null ? array($marked) : array());
		}
		$marked = array_map(function($r){
			if (!$r instanceof Range && method_exists($r, 'getRange')) $r = $r->getRange();
			if (!$r instanceof Range)
				trigger_error(vartype($r)." passed as marked range is neither a Range nor does it implement the getRange() function", E_USER_ERROR);
			return $r;
		}, $marked);
		$mb = count($marked);
		$marked = array_filter($marked, function($r){ return $r instanceof Range; });
		
		$this->range   = $range;
		$this->marked  = $marked;
	}
	
	public function __toString()
	{
		global $ENABLE_COLORS;
		
		if (!is_array($this->marked)) {
			$this->marked = array();
		}
		
		$source = null;
		if ($this->range) {
			$source = $this->range->getFile();
		} else if (count($this->marked) > 0) {
			$source = $this->marked[0]->getFile();
		}
		
		$t = $this->type.':';
		if ($this->type == 'error' && $ENABLE_COLORS)   $t = "\033[1;31m$t\033[0m";
		if ($this->type == 'warning' && $ENABLE_COLORS) $t = "\033[1;33m$t\033[0m";
		
		$msg = str_replace("\n", "\n    : ", $this->message);
		$o = "$t $msg";
		if ($source) {
			$sfr  = basename($source->getPath());
			if ($this->range) {
				$sfr .= ':';
				$sfr .= ($this->range->getStart()->getLine()+1).':'.$this->range->getStart()->getColumn();
			}
			$o = "$sfr: $o";
		}
		
		$lines = ($this->range ? range($this->range->getStart()->getLine(), $this->range->getEnd()->getLine()) : array());
		foreach ($this->marked as $r) {
			if (!$source) $source = $r->getFile();
			$lines = array_merge($lines, range($r->getStart()->getLine(), $r->getEnd()->getLine()));
		}
		$lines = array_unique($lines);
		sort($lines);
		
		if (count($lines) > 0) {
			$ls = explode("\n", $source->getContents());
			
			$whitelead_min = null;
			foreach ($lines as $l) {
				preg_match('/^\s*/', $ls[$l], $match);
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
				$line = $ls[$l];
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
				if ($ENABLE_COLORS) $marks = "\033[0;36m$marks\033[0m";
			
				$prefix = sprintf('%4d', $l+1);
				$pad = str_repeat(' ', strlen($prefix));
				$o .= "\n";
				$o .= "$prefix| $line\n";
				$o .= "$pad| $marks";
			}
		}
		
		return $o;
	}
}
