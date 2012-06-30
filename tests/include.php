<?php
require_once __DIR__."/../source/autoload.php";

$TEST_OUTPUT_DIR = __DIR__."/../build/tests";
if (!file_exists($TEST_OUTPUT_DIR))
	mkdir($TEST_OUTPUT_DIR);
