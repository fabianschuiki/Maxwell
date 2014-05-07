<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/parser");
$manager->push();

$file = $manager->getSourceFileAtPath("$TEST_DIR/parser.mw");

$lexer = new Lexer\Lexer($file);
$lexer->run();
$issues->reportAndExitIfFatal();

$parser = new Parser\Parser($lexer->getTokens());
$parser->run();
$issues->reportAndExitIfFatal();

$issues->pop();
$issues->report();

$manager->pop();