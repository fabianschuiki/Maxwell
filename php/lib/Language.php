<?php

class Language
{
	static public $symbols;
	
	static public $symbolCombinations = array(
		'==', '!=', "=>", ":=", "->"
	);
	
	static public $identifierSymbols = array("~");
	
	static public $keywords = array(
		'func', 'type', 'primitive', 'if', 'else', 'for', 'return', 'inline', 'import',
	);
	
	static public $unaryOperators = array(
		array('-'),
	);
	
	static public $binaryOperators = array(
		array('=', ':='),
		array('==', '!=', '<', '>', '<=', '>='),
		array('+', '-'),
		array('*', '/'),
	);
}

Language::$symbols = array_merge(
	range(0x21, 0x2F),
	range(0x3A, 0x3F),
	range(0x5B, 0x5E),
	range(0x7B, 0x7E)
);
