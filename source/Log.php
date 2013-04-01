<?php
/* Copyright © 2013 Fabian Schuiki */

class Log
{
	/**
	 * Prints the given output line to the console, prepending it with the
	 * given $class and $info metadata. Colors!
	 */
	static public function println($ln, $class = null, $info = null)
	{
		$dirty = false;
		if ($class) {
			echo "\033[1m$class\033[0m";
			$dirty = true;
		}
		if ($info) {
			if ($dirty)
				echo " ";
			echo "\033[36;1m$info\033[0m";
			$dirty = true;
		}
		if ($dirty)
			echo ": ";
		echo $ln;
		echo "\n";
	}
}