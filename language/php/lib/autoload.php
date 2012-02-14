<?php
/// Automatically loads requested classes from the lib directory.
spl_autoload_register(function($class) {
	$path = __DIR__.'/'.trim(str_replace('\\', '/', $class), '/').'.php';
	require_once $path;
});
