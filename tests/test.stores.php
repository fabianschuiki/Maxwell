<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/stores");
$manager->push();


$file = $manager->getSourceFileAtPath("$TEST_DIR/parser.mw");

$lexer = new Lexer\Lexer($file);
$lexer->run();
$issues->reportAndExitIfFatal();
$manager->getTokenStore()->setTokensForFile($lexer->getTokens(), $lexer->getFile());

$parser = new Parser\Parser($lexer->getTokens());
$parser->run();
$issues->reportAndExitIfFatal();


$manager->pop();

$issues->pop();
$issues->report();