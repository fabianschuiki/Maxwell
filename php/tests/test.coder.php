<?php
require_once __DIR__.'/include.php';

$root = new Coder\Element("root");
$some = $root->makeElement("token");
$some->setAttribute("id", 1234);
$some->setAttribute("range", "45-95");
$some = $root->makeElement("token");
$some->setAttribute("id", 6316);
$some->setAttribute("range", "214oi");

$ser = new Coder\XMLCoder;
$xml = $ser->encode($root);

file_put_contents($TEST_OUTPUT_DIR."/coder.xml", $xml);