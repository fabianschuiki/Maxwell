<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/stores");
$manager->push();
$tokenStore = $manager->getTokenStore();


$file = $manager->getSourceFileAtPath("$TEST_DIR/parser.mw");

if (true || $tokenStore->isFileOutdated($file)) {
	$lexer = new Lexer\Lexer($file);
	$lexer->run();
	$issues->reportAndExitIfFatal();
	$tokenStore->setTokensForFile($lexer->getTokens(), $lexer->getFile());
}

$parser = new Parser\Parser($tokenStore->getTokensForFile($file));
$parser->run();
$issues->reportAndExitIfFatal();


$manager->pop();

$issues->pop();
$issues->report();