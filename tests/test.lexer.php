<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$file = new Source\File(__DIR__."/lexer.mw");

$lexer = new Lexer($file);
$lexer->run();

$issues->pop();
$issues->report();