<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$file = new SourceFile(__DIR__."/lexer.mw");

$lexer = new Lexer($file);
//$lexer->run();

$issues->pop();
$issues->report();