<?php
$ENABLE_COLORS = getenv("TERM") && (`tput colors` > 2);

function vartype($v)
{
	if (is_object($v))
		return get_class($v);
	return gettype($v);
}

function exception_handler($exception)
{
	echo "\n";
	echo "\033[31;1m*** EXCEPTION ***\033[0m (".get_class($exception).")\n";
	echo "Message: \033[1m{$exception->getMessage()}\033[0m\n";
	echo "File: \033[36;1m".str_replace(__DIR__."/", "", $exception->getFile())."\033[0m line \033[36m".$exception->getLine()."\033[0m\n";
	echo "\n";

	// Print the backtrace.
	echo str_replace(__DIR__."/", "", $exception->getTraceAsString())."\n";
	echo "\n";

	exit(1);
}
set_exception_handler("exception_handler");

function error_handler($no, $str, $file, $line) {
    $e = new ErrorException($str, $no, 0, $file, $line);
    exception_handler($e);
}
set_error_handler("error_handler");