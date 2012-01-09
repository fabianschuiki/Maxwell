#!/usr/bin/php
<?php
require_once __DIR__.'/lib/lexer.php';
require_once __DIR__.'/lib/parser.php';
require_once __DIR__.'/lib/analyzer.php';
require_once __DIR__.'/lib/compiler-php.php';

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
echo $parser->rootBlock->desc()."\n\n";


//Analyze the syntax tree.
/*echo "\033[1m"."Analyzed Syntax Tree:\n"."\033[0m";
$analyzer = new Analyzer\Analyzer($parser->rootBlock);
$analyzer->execute();

//Dump the analyzed syntax tree.
//print_r($parser->rootBlock);


//Compile the syntax tree down to PHP.
echo "\033[1m"."Compiled PHP Code:\n"."\033[0m";
$compiler = new Compiler\Compiler($parser->rootBlock);
$compiler->execute();

//Dump the compiled code.
echo $compiler->code."\n";

//Generate the output file.
$outputFile = __DIR__.'/compiled/'.basename($inputFile).'.php';
if (!file_exists(dirname($outputFile)))
	mkdir(dirname($outputFile), 0777, true);
file_put_contents($outputFile, "<?php\n".$compiler->code);*/
