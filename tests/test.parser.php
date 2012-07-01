<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$file = new Source\File(__DIR__."/parser.mw");

$lexer = new Lexer\Lexer($file);
$lexer->run();
$issues->reportAndExitIfFatal();
$serializer = new Lexer\TokenSerializer($lexer->getTokens());
file_put_contents("$TEST_OUTPUT_DIR/parser.tokens", $serializer->getXML());

$parser = new Parser\Parser($lexer->getTokens());
$parser->run();
$issues->reportAndExitIfFatal();

$issues->pop();
$issues->report();