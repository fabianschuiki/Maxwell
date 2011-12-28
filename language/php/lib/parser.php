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
		$this->rootBlock = $this->parseBlock($this->rootGroup->children);
	}
	
	/** Parses a sequence of statements. */
	private function parseBlock($tokens) {
		$block = new AST\Block();
		$scanner = new Scanner($tokens);
		while ($tokens = $scanner->scanStatement()) {
			
			//Depending on whether the last token is a ; or a {} block, we call a different
			//statement parsing function.
			$lastToken = $tokens[count($tokens) - 1];
			if ($lastToken->type == 'symbol' && $lastToken->text == ';') {
				array_pop($tokens);
				$stmt = $this->parseBlocklessStatement($tokens);
			} else {
				$stmt = $this->parseBlockStatement($tokens);
			}
			
			//If we obtained a valid statement, add it to the block.
			if ($stmt instanceof AST\Statement) {
				$block->statements[] = $stmt;
			} else {
				$this->issues[] = new Issue(
					'unable to parse into statement',
					$tokens
				);
			}
		}
		return $block;
	}
	
	/** Parses statements that don't have a trailing block. */
	private function parseBlocklessStatement($tokens) {
		
		//Capture keyword-introduced statements.
		if ($tokens[0]->isKeyword()) {
			$keyword = array_shift($tokens);
			
			//Capture return statements.
			if ($keyword->text == 'return') {
				$s = new AST\ReturnStmt;
				$s->exprs = array();
				$scanner = new Scanner($tokens);
				while ($t = $scanner->scan('symbol', ',', false)) {
					$s->exprs[] = $this->parseExpression($t);
				}
				return $s;
			}
		}
		
		//This seems to be an expression statement.
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
		
		//Capture function calls.
		if (count($tokens) >= 2 && $tokens[count($tokens) - 1]->isGroup('()')) {
			return $this->parseFunctionCallExpr($tokens);
		}
		
		//Check whether this seems to be a variable expression.
		if (count($tokens) == 2 && $tokens[0]->isIdentifier() && $tokens[1]->isIdentifier()) {
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
			
			//Identifiers.
			if ($token->isIdentifier()) {
				$e = new AST\IdentifierExpr;
				$e->identifier = $token;
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
	
	/** Parses the tokens as if they were an anonymous function expression. */
	private function parseFunctionExpr($tokens) {
		//Pop off last token which needs to be a block.
		$body = array_pop($tokens);
		if (!$body || !$body->isGroup('{}')) {
			$this->issues[] = new Issue(
				'function needs to have a body { }',
				$body
			);
			return null;
		}
		
		//Create a scanner for the input and outputs.
		$scanner = new Scanner($tokens);
		
		//Try to separate inputs from outputs.
		$arrow = $scanner->find('symbol', '=>');
		if ($arrow === false) {
			$arrow = count($tokens) - 1;
		}
		$inputs  = array_slice($tokens, 0, $arrow);
		$outputs = array_slice($tokens, $arrow + 1);
		
		//Create the function expression.
		$e = new AST\FunctionExpr;
		$e->inputs  = $this->parseFunctionArgs($inputs);
		$e->outputs = $this->parseFunctionArgs($outputs);
		$e->body    = $this->parseBlock($body->children);
		return $e;
	}
	
	/** Parses the tokens as if they were the argument list of a function. */
	private function parseFunctionArgs($tokens) {
		if (count($tokens) == 0) {
			return null;
		}
		if ($tokens[0]->isGroup('()')) {
			$tokens = $tokens[0]->children;
		}
		
		//Create a scanner for the tokens.
		$scanner = new Scanner($tokens);
		
		//Scan the arguments which are separated by commas (,).
		$arguments = array();
		while ($t = $scanner->scan('symbol', ',')) {
			$a = $this->parseFunctionArg($t);
			if ($a)
				$arguments[] = $a;
		}
		
		return $arguments;
	}
	
	/** Parses the tokens as if they were a single function argument. */
	private function parseFunctionArg($tokens) {
		if (count($tokens) == 0) {
			$this->issues[] = new Issue(
				'function argument needs at least a name'
			);
			return null;
		}
		
		$a = new AST\FunctionArg;
		$a->name = $tokens[0];
		$a->type = $tokens[1];
		return $a;
	}
	
	/** Parses the tokens as if they were a function call. */
	private function parseFunctionCallExpr($tokens) {
		$args = array_pop($tokens);
		$e = new AST\FunctionCallExpr;
		$e->name = $tokens[0];
		$e->arguments = $this->parseFunctionCallArgs($args->children);
		return $e;
	}
	
	/** Parses the tokens as if they were arguments to a function call. */
	private function parseFunctionCallArgs($tokens) {
		$scanner = new Scanner($tokens);
		$arguments = array();
		while ($t = $scanner->scan('symbol', ',')) {
			$a = $this->parseFunctionCallArg($t);
			if ($a)
				$arguments[] = $a;
		}
		return $arguments;
	}
	
	/** Parses the tokens as if they were one single argument to a function call. */
	private function parseFunctionCallArg($tokens) {
		$scanner = new Scanner($tokens);
		$colon = $scanner->find('symbol', ':');
		$a = new AST\FunctionCallArg;
		if ($colon !== false) {
			if ($colon != 1) {
				$this->issues[] = new Issue(
					'garbage in front of function call argument name',
					array_slice($tokens, 0, $colon - 1)
				);
				return null;
			}
			$a->name = $tokens[$colon - 1];
			$tokens = array_slice($tokens, $colon + 1);
		}
		$a->expr = $this->parseExpression($tokens);
		return $a;
	}
	
	/** Parses statements that have a trailing block, like functions or flow controllers. */
	private function parseBlockStatement($tokens) {
	
		//This seems to be a function.
		return $this->parseFunctionStmt($tokens);
	}
	
	/** Parses the tokens as if they were a function statement. */
	private function parseFunctionStmt($tokens) {
		if (!$tokens[0]->isIdentifier()) {
			$this->issues[] = new Issue(
				'first token needs to be the function name',
				$tokens[0]
			);
			return null;
		}
		
		$s = new AST\FunctionStmt;
		$s->name = $tokens[0];
		$s->function = $this->parseFunctionExpr(array_slice($tokens, 1));
		return $s;
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
		if (!is_array($this->tokens) || count($this->tokens) == 0)
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
	public function find($type = null, $text = null, $fromRight = false) {
		for ($i = 0; $i < count($this->tokens); $i++) {
			$index = ($fromRight ? count($this->tokens) - 1 - $i : $i);
			$t = $this->tokens[$index];
			if ((!$type || $t->type == $type || (is_array($type) && in_array($t->type, $type))) &&
				(!$text || $t->text == $text || (is_array($text) && in_array($t->text, $text)))) {
				return $index;
			}
		}
		return false;
	}
	
	/** Scans up to the next token that matches. */
	public function scan($type = null, $text = null, $withToken = true) {
		if (!is_array($this->tokens) || count($this->tokens) == 0)
			return null;
		$i = $this->find($type, $text);
		if ($i === false) {
			$i = count($this->tokens);
		}
		$res          = array_slice($this->tokens, 0, ($withToken ? $i+1 : $i));
		$this->tokens = array_slice($this->tokens, $i+1);
		return $res;
	}
}

//Initialize the operators.
Parser::$operators = array(
	array('='),
	array('+', '-'),
	array('*', '/'),
);
