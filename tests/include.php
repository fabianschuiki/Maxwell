<?php
require_once __DIR__."/../source/autoload.php";
error_reporting(E_ALL);

$TEST_OUTPUT_DIR = __DIR__."/../build/tests";
if (!file_exists($TEST_OUTPUT_DIR))
	mkdir($TEST_OUTPUT_DIR);
