<?php
/// Automatically loads requested classes from the lib directory.
spl_autoload_register(function($class) {
	$path = __DIR__.'/'.trim(str_replace('\\', '/', $class), '/').'.php';
	if (!file_exists($path)) return false;
	require_once $path;
});
