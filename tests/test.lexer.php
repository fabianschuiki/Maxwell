<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$file = new Source\File(__DIR__."/lexer.mw");

$lexer = new Lexer\Lexer($file);
$lexer->run();

$serializer = new Lexer\TokenSerializer($lexer->getTokens());
file_put_contents("$TEST_OUTPUT_DIR/lexer.tokens", $serializer->getXML());

$issues->pop();
$issues->report();