#!/usr/bin/php
<?php
require_once __DIR__.'/lib/lexer.php';

//Read the input file.
$inputFile = __DIR__.'/../debug.mw';
$input = file_get_contents($inputFile);

//Lexer run.
$lexer = new Lexer\Lexer($input);
$lexer->execute();

//Dump the lexer results.
echo $lexer->rootGroup->desc()."\n";
