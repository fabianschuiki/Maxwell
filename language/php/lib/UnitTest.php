<?php

class UnitTest
{
	static public function group($name)
	{
		echo "\n\033[1m$name\033[0m\n";
	}
	
	static public function test($label, $result, $desired)
	{
		$result  = strval(!$result ? 'nil' : $result);
		$desired = strval($desired);
		if ($result != $desired) {
			echo "- \033[36m$label\033[0m: \033[31mFAILED\033[0m, \033[36m$result\033[0m instead of $desired\n";
			/*$trace = debug_backtrace();
			 $ entry = array_shift($*trace);
			 $filename = basename($entry['file']);
			 $lines = file($entry['file']);
			 $linenum = $entry['line'];
			 $line = $lines[$linenum-1];
			 preg_match('/^.*?\((.*?)\);\s*$/', $line, $matches);
			 $line = $matches[1];
			echo "-> $filename.$linenum: $line\n";*/
		} else {
			echo "- \033[36m$label\033[0m: \033[32mpassed\033[0m, $desired\n";
		}
	}
}