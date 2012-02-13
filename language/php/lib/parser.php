<?php
namespace Parser;

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
	
	static public $languageConstants = array(
		'nil', 'true', 'false',
	);
	
	//Tokens to be parsed.
	protected $rootGroup;
	
	//The resulting root block of statements.
	public $rootBlock;
	
	//Issues encountered while parsing the syntax tree.
	public $issues;
	
	/** Creates a new issue. */
	public function issue($message, $tokens = null)
	{
		$i = new Issue($message, $tokens);
		$this->issues[] = $i;
		$n = new ASTNode('issue');
		$n->issue = $i;
		return $n;
	}
	
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
		$block = new ASTNode('block');
		$block->statements = array();
		$scanner = new Scanner($tokens);
		while ($tokens = $scanner->scan('symbol', ';')) {
			array_pop($tokens);
			if (!count($tokens))
				continue;
			$stmt = $this->parseStatement($tokens);
			if (!$stmt) {
				$stmt = $this->issue('unable to parse into statement', $tokens);
			}
			$block->statements[] = $stmt;
		}
		return $block;
	}
	
	private function parseStatement($tokens) {
		$s = new ASTNode('stmt.expr');
		$s->expr = $this->parseExpression($tokens);
		return $s;
	}
	
	private function parseExpression($tokens) {
		$tc = count($tokens);
		$scanner = new Scanner($tokens);
		
		if ($tc == 1 && $tokens[0]->isGroup('()')) {
			return $this->parseExpression($tokens[0]->children);
		}
		
		//Operators
		foreach (self::$operators as $operators) {
			$op = $scanner->find('symbol', $operators, true);
			if ($op !== false) {
				$e = new ASTNode('expr.op.binary');
				$e->op = $tokens[$op];
				$e->lhs = $this->parseExpression(array_slice($tokens, 0, $op));
				$e->rhs = $this->parseExpression(array_slice($tokens, $op + 1));
				return $e;
			}
		}
		
		//Variables
		if ($tc == 2 && $tokens[0]->isIdentifier() && $tokens[1]->isIdentifier()) {
			$e = new ASTNode('expr.var');
			$e->name = $tokens[0];
			$e->type = $tokens[1];
			return $e;
		}
		
		//Constants
		if ($tc == 1) {
			$t = $tokens[0];
			$kind = null;
			if ($t->isNumeric()) $kind = 'expr.const.num';
			if ($t->isString())  $kind = 'expr.const.string';
			if ($t->isIdentifier() && in_array($t->text, static::$languageConstants)) {
				$kind = 'expr.const.lang';
			}
			if ($kind) {
				$e = new ASTNode($kind);
				$e->value = $t;
				return $e;
			}
		}
		
		//Identifier
		if ($tc == 1 && $tokens[0]->isIdentifier()) {
			$e = new ASTNode('expr.ident');
			$e->name = $tokens[0];
			return $e;
		}
		
		return $this->issue('unable to parse into expression', $tokens);
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
		return $this->desc();
	}
	public function desc($withLocation = true) {
		$s = '';
		if ($withLocation) {
			$s .= $this->range.": ";
		}
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

class ASTNode
{
	public $kind;
	public function __construct($kind) {
		$this->kind = $kind;
	}
	public function nodes() {
		switch ($this->kind) {
		case 'block':          return $this->statements; break;
		case 'stmt.expr':      return array($this->expr); break;
		case 'expr.op.binary': return array($this->lhs, $this->rhs); break;
		}
		return array();
	}
	public function desc($indent = 0) {
		switch ($this->kind) {
			case 'issue': {
				return '<'.$this->issue->desc(false).'>';
			}
			case 'block': {
				$in = str_repeat('    ', $indent);
				$s = '{';
				foreach ($this->statements as $stmt) {
					$s .= "\n".$in.'    '.$stmt->desc($indent + 1);
				}
				$s .= "\n".$in.'}';
				return $s;
			}
			case 'stmt.expr': {
				return $this->expr->desc().';';
			}
			case 'expr.var': {
				return varname($this->name).' '.typename($this->type);
			}
			case 'expr.op.binary': {
				$l = $this->lhs->desc();
				$r = $this->rhs->desc();
				if ($this->lhs->kind == 'expr.op.binary') $l = "($l)";
				if ($this->rhs->kind == 'expr.op.binary') $r = "($r)";
				return $l.' '.$this->op->text.' '.$r;
			}
			case 'expr.const.num': {
				return numeric($this->value);
			}
			case 'expr.const.string': {
				return string($this->value);
			}
			case 'expr.const.lang': {
				return keyword($this->value);
			}
			case 'expr.ident': {
				return $this->name->text;
			}
		}
	}
}

//Initialize the operators.
Parser::$operators = array(
	array('=', ':='),
	array('+', '-'),
	array('*', '/'),
);
