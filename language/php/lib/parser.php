<?php
namespace Parser;
require_once __DIR__.'/ast.php';

/** Converts an array of tokens into a string. */
function tokens2str($tokens) {
	$s = '';
	foreach ($tokens as $t) {
		if ($s != '')
			$s .= ' ';
		$s .= $t->desc(0);
	}
	return $s;
}

class Parser
{
	static public $operators;
	
	//Tokens to be parsed.
	protected $rootGroup;
	
	//The resulting root block of statements.
	public $rootBlock;
	
	//Issues encountered while parsing the syntax tree.
	public $issues;
	
	/** Constructs a parser for the given root group. */
	public function __construct($rootGroup) {
		$this->rootGroup = $rootGroup;
	}
	
	/** Parses the root group into an abstract syntax tree. */
	public function execute() {
		$this->rootBlock = new AST\Block();
		
		//Scan the group statement-wise, calling the parsing function based on whether the
		//statement is followed by a block ({...}) or not (;).
		$scanner = new Scanner($this->rootGroup->children);
		while ($tokens = $scanner->scanStatement()) {
			//echo "scanned: ".tokens2str($tokens)."\n";
			$lastToken = $tokens[count($tokens) - 1];
			if ($lastToken->type == 'symbol' && $lastToken->text == ';') {
				array_pop($tokens);
				$stmt = $this->parseBlocklessStatement($tokens);
			} else {
				$stmt = $this->parseBlockStatement($tokens);
			}
			if ($stmt instanceof AST\Statement) {
				$this->rootBlock->statements[] = $stmt;
			} else {
				$this->issues[] = new Issue(
					'unable to parse into statement',
					$tokens
				);
			}
		}
	}
	
	/** Parses statements that don't have a trailing block. */
	private function parseBlocklessStatement($tokens) {
		echo "scanned: ".tokens2str($tokens)."\n";
		$s = new AST\ExpressionStmt;
		$s->expr = $this->parseExpression($tokens);
		return $s;
	}
	
	/** Parses the tokens as if they formed an expression. */
	private function parseExpression($tokens) {
		if (count($tokens) == 0) {
			$this->issues[] = new Issue('no tokens to be parsed');
			return null;
		}
		
		//Create a scanner for the tokens.
		$scanner = new Scanner($tokens);
		
		//Try to parse any operator expressions.
		foreach (self::$operators as $operators) {
			$op = $scanner->find('symbol', $operators, true);
			if ($op !== false) {
				return $this->parseBinaryOperatorExpr(
					$tokens[$op],
					array_slice($tokens, 0, $op),
					array_slice($tokens, $op + 1)
				);
			}
		}
		
		//Check whether this seems to be a variable expression.
		if ($tokens[0]->isIdentifier() && (!$tokens[1] || $tokens[1]->isIdentifier())) {
			return $this->parseVariableExpr($tokens);
		}
		
		//Capture expressions of only one token.
		if (count($tokens) == 1) {
			$token = $tokens[0];
			
			//Expressions in paranthesis.
			if ($token->is('group') && $token->subtype == '()') {
				return $this->parseExpression($token->children);
			}
			
			//Numeric values.
			if ($token->isNumeric()) {
				$e = new AST\NumericExpr;
				$e->value = $token;
				return $e;
			}
			
			//String values.
			if ($token->isString()) {
				$e = new AST\StringExpr;
				$e->value = $token;
				return $e;
			}
		}
		
		//Now idea what to do with these tokens.
		$this->issues[] = new Issue(
			'cannot form expression',
			$tokens
		);
		return null;
	}
	
	/** Parses the tokens as if they were a variable expression. */
	private function parseVariableExpr($tokens) {
		if (count($tokens) > 2) {
			$this->issues[] = new Issue(
				'superfluous tokens in variable expression',
				array_slice($tokens, 2)
			);
		}
		$e = new AST\VariableExpr;
		$e->name = $tokens[0];
		$e->type = $tokens[1];
		return $e;
	}
	
	/** Parses the tokens as if they were an assignment expression. */
	private function parseBinaryOperatorExpr($op, $lhs, $rhs) {
		$e = new AST\BinaryOperatorExpr;
		$e->operator = $op;
		$e->lhs = $this->parseExpression($lhs);
		$e->rhs = $this->parseExpression($rhs);
		return $e;
	}
	
	/** Parses statements that have a trailing block, like functions or flow controllers. */
	private function parseBlockStatement($tokens) {
		echo "scanned: ".tokens2str($tokens)."\n";
	}
}

class Issue
{
	public $description;
	public $tokens;
	public $range;
	
	public function __construct($description, $tokens = null) {
		$this->description = $description;
		if ($tokens) {
			$this->tokens = (is_array($tokens) ? $tokens : array($tokens));
		} else {
			$this->tokens = array();
		}
		if ($this->tokens[0]->range) {
			$this->range = clone $this->tokens[0]->range;
			$this->range->end = $this->tokens[count($this->tokens) - 1]->range->end;
		}
	}
	public function __toString() {
		$s = '';
		$s .= $this->range.": ";
		$s .= "\033[41m".$this->description."\033[0m";
		if (count($this->tokens)) {
			$s .= ": ".tokens2str($this->tokens);
		}
		return $s;
	}
}

class Scanner
{
	//Tokens to be scanned.
	protected $tokens;
	
	/** Creates a new scanner for scanning the given tokens. */
	public function __construct($tokens) {
		$this->tokens = $tokens;
	}
	
	/** Returns whether we're done scanning tokens. */
	public function isEOT() {
		return !is_array($this->tokens) || count($this->tokens) == 0;
	}
	
	/** Scans up to the next statement delimiter (; or {). */
	public function scanStatement() {
		if (!is_array($this->tokens))
			return null;
		$res = array();
		for ($i = 0; $i < count($this->tokens); $i++) {
			$t = $this->tokens[$i];
			$res[] = $t;
			if (($t->type == 'symbol' && $t->text == ';') || ($t->type == 'group'  && $t->subtype == '{}')) {
				break;
			}
		}
		$this->tokens = array_slice($this->tokens, $i+1);
		return (count($res) ? $res : null);
	}
	
	/** Returns the position of the first token that matches type and text. */
	public function find($type, $text = null, $fromRight = false) {
		for ($i = 0; $i < count($this->tokens); $i++) {
			$index = ($fromRight ? count($this->tokens) - 1 - $i : $i);
			$t = $this->tokens[$index];
			if ($t->type == $type || (is_array($type) && in_array($t->type, $type))) {
				if (!$text || $t->text == $text || (is_array($text) && in_array($t->text, $text))) {
					return $index;
				}
			}
		}
		return false;
	}
}

//Initialize the operators.
Parser::$operators = array(
	array('='),
	array('+', '-'),
	array('*', '/'),
);
