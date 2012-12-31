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
				if ($r == null) continue;
				if (!$r instanceof Range && method_exists($r, 'getHumanRangeIfPossible')) $r = $r->getHumanRangeIfPossible();
				if (!$r instanceof Range && method_exists($r, 'getRange')) $r = $r->getRange();
				if (!$r instanceof Range)
					trigger_error(vartype($r)." passed as range is neither a Range nor does it implement the getRange() function", E_USER_ERROR);
				$ranges[] = $r;
			}
			$range = Range::union($ranges);
		}
		if (!$range instanceof Range && method_exists($range, 'getHumanRangeIfPossible')) {
			$range = $range->getHumanRangeIfPossible();
		}
		if (!$range instanceof Range && method_exists($range, 'getRange')) {
			$range = $range->getRange();
		}
		
		if (!is_array($marked)) {
			$marked = ($marked != null ? array($marked) : array());
		}
		$marked = array_map(function($r){
			if (!$r instanceof Range && method_exists($r, 'getHumanRangeIfPossible')) $r = $r->getHumanRangeIfPossible();
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
		
		//Make a list of source files this issue references.
		$sourceFiles = array();
		if ($this->range) $sourceFiles[] = $this->range->getFile();
		foreach ($this->marked as $m) {
			$f = $m->getFile();
			$found = false;
			foreach ($sourceFiles as $sf) {
				if ($sf->getPath() == $f->getPath()) {
					$found = true;
					break;
				}
			}
			if (!$found) {
				$sourceFiles[] = $f;
			}
		}
		
		//Decide the main source file, which essentially is the range's source file.
		if (count($sourceFiles)) {
			$source = $sourceFiles[0];
		} else {
			$source = null;
		}
		
		//Assemble a list of marked ranges per source file.
		$markedPerFile = array();
		foreach ($this->marked as $m) {
			$markedPerFile[$m->getFile()->getPath()][] = $m;
		}
		
		//Assemble the message
		$msg = $this->type.':';
		if ($this->type == 'error' && $ENABLE_COLORS)   $msg = "\033[1;31m$msg\033[0m";
		if ($this->type == 'warning' && $ENABLE_COLORS) $msg = "\033[1;33m$msg\033[0m";
		$msg .= " ".str_replace("\n", "\n    : ", $this->message);
		
		//If this issue has a main range, prefix the message with that range.
		if ($source) {
			$sfr = basename($source->getPath());
			if ($this->range) {
				$sfr .= ':';
				$sfr .= ($this->range->getStart()->getLine()+1).':'.($this->range->getStart()->getColumn()+1);
			}
			$msg = "$sfr: $msg";
		}
		
		//Iterate through all the source files and dump the required code snippet.
		$output = $msg;
		foreach ($sourceFiles as $file) {
			$output .= "\n";
			if ($file !== $source) {
				$output .= "- see ".basename($file->getPath()).":\n";
			}
			$output .= $this->getMarkedFileSnippet($file, ($this->range && $this->range->getFile() === $file ? $this->range : null), @$markedPerFile[$file->getPath()]);
		}
		
		return $output;
	}
	
	private function getMarkedFileSnippet(Source\File $file, Source\Range $range = null, array $marked = null)
	{
		global $ENABLE_COLORS;
		
		$output = "";
		if (!$marked) {
			$marked = array();
		}
		
		$lines = ($range ? range($range->getStart()->getLine(), $range->getEnd()->getLine()) : array());
		foreach ($marked as $r) {
			$lines = array_merge($lines, range($r->getStart()->getLine(), $r->getEnd()->getLine()));
		}
		$lines = array_unique($lines);
		sort($lines);
		
		if (count($lines) > 0) {
			$ls = explode("\n", $file->getContents());
			
			$whitelead_min = null;
			foreach ($lines as $l) {
				preg_match('/^\s*/', $ls[$l], $match);
				$whitelead = strlen(str_replace("\t", "    ", $match[0]));
				if (!$whitelead_min || $whitelead < $whitelead_min) $whitelead_min = $whitelead;
			}
			if (!$whitelead_min) $whitelead_min = 0;
			
			$pl = $lines[0]-1;
			$output .= "";
			foreach ($lines as $l) {
				$skipped = ($l != $pl+1);
				if ($skipped) $output .= "\r    ~";
				
				$pl = $l;
				$line = $ls[$l];
				$marks = '';
				for ($i = 0; $i < strlen($line); $i++) {
					$mark = ($line[$i] == "\t" ? "\t" : " ");
					if ($range && $range->contains($l, $i)) {
						$mark = ($mark == "\t" ? "    " : "^");
					} else {
						foreach ($marked as $r) {
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
				if (strlen($output)) $output .= "\n";
				$output .= "$prefix| $line\n";
				$output .= "$pad| $marks";
			}
		}
		
		return $output;
	}
}
