<?php

class Language
{
	static public $symbols;
	
	static public $symbolCombinations = array(
		'==', '!=', "=>", ":=", "->"
	);
	
	static public $identifierSymbols = array("~");
	
	static public $keywords;
	static public $statementKeywords = array(
		'func', 'type', 'primitive', 'if', 'else', 'for', 'return', 'inline', 'import', 'native', 'package', 'external',
	);
	static public $expressionKeywords = array(
		'var', 'new',
	);
	
	static public $operators;
	static public $unaryOperators = array(
		array('-', '!'),
	);
	static public $binaryOperators = array(
		array('=', ':='),
		array('==', '!=', '<', '>', '<=', '>='),
		array('+', '-'),
		array('*', '/'),
		array('..'),
	);
}

Language::$symbols = array_merge(
	range(0x21, 0x2F),
	range(0x3A, 0x3F),
	range(0x5B, 0x5E),
	range(0x7B, 0x7E)
);

Language::$keywords = array_merge(Language::$statementKeywords, Language::$expressionKeywords);

Language::$operators = array_unique(array_reduce(array_merge(
		Language::$unaryOperators,
		Language::$binaryOperators
	),
	function($a, $b) {
		return array_merge($a, $b);
	},
	array()
));

Language::$symbolCombinations = array_unique(array_merge(Language::$symbolCombinations, Language::$operators));
