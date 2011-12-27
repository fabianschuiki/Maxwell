#!/usr/bin/php
<?php
require_once __DIR__.'/lib/lexer.php';
require_once __DIR__.'/lib/parser.php';

//Read the input file.
$inputFile = __DIR__.'/../debug.mw';
$input = file_get_contents($inputFile);

//Run the input through the lexer.
echo "\033[1m"."Lexical Analysis:\n"."\033[0m";
$lexer = new Lexer\Lexer($input);
$lexer->inputFileName = basename($inputFile);
$lexer->execute();

//Dump the lexer results.
echo $lexer->rootGroup->desc()."\n";

//Run the tokens through the parser.
echo "\033[1m"."Abstract Syntax Tree:\n"."\033[0m";
$parser = new Parser\Parser($lexer->rootGroup);
$parser->execute();

//Dump the parser issues.
if (count($parser->issues)) {
	foreach ($parser->issues as $i) {
		echo $i."\n";
	}
	//exit;
	echo "\n";
}

//Dump the syntax tree.
echo $parser->rootBlock->desc()."\n";
