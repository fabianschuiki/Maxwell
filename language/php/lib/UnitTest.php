<?php

class UnitTest
{
	static public function test($result, $desired)
	{
		$result  = strval($result);
		$desired = strval($desired);
		if ($result != $desired) {
			$trace = debug_backtrace();
			$entry = array_shift($trace);
			$filename = basename($entry['file']);
			$lines = file($entry['file']);
			$linenum = $entry['line'];
			$line = $lines[$linenum-1];
			preg_match('/^.*?\((.*?)\);\s*$/', $line, $matches);
			$line = $matches[1];
			echo "- $desired: \033[31mFAILED\033[0m, got \033[36m$result\033[0m\n  -> $filename.$linenum: $line\n";
		} else {
			echo "- $desired: \033[32mpassed\033[0m\n";
		}
	}
}