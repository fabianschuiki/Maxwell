<?php
namespace Lexer;
require_once __DIR__.'/helper.php';

class Lexer
{
	//Symbol ranges.
	static public $symbols = array();
	
	//Symbol combinations that are merged into one symbol token.
	static public $symbolCombinations = array(
		"=>"
	);
	
	//Keywords.
	static public $keywords = array(
		'if', 'else',
		'return',
	);
	
	//The input string that is to be tokenized.
	protected $input;
	public $inputFileName;
	
	//The parsed root group node.
	public $rootGroup;
	
	//Any issues the lexer ran into.
	public $issues;
	
	/** Constructs the lexer for tokenizing the given input. */
	public function __construct($input) {
		$this->input = $input;
	}
	
	/** Tokenizes the input. */
	public function execute() {
		$issues = array();
		
		//Accumulation buffer for tokens.
		$bufferType  = null;
		$bufferRange = new Range;
		$buffer      = "";
		
		//Keep the name around.
		$bufferRange->file = $this->inputFileName;
		
		//Location tracking.
		$loc = new Location;
		
		//Keep a group stack.
		$this->rootGroup = new Group('group', null, 'root');
		$groupStack = array($this->rootGroup);
		
		//Iterate through every character in the input string.
		$context = 'code';
		$len = strlen($this->input);
		for ($i = 0; $i < $len + 1; $i++) {
			$ppc = $pc;
			$pc  = $c;
			$c   = ($i < $len ? $this->input[$i] : null);
			$nc  = $this->input[$i+1];
			
			//Advance the location.
			if ($c == "\n") {
				$loc->line++;
				$loc->column = 0;
			}
			
			//Process the character based on the context.
			$newBufferType = null;
			$wrapUpAnyway  = false;
			switch ($context) {
				//Inside normal code.
				case 'code': {
					//Comments
					if ($c == '/' && $nc == '/') {
						$context = 'comment.line';
						break;
					}
					if ($c == '/' && $nc == '*') {
						$context = 'comment.block';
						break;
					}
					
					//Strings
					if ($c == '"') {
						$context = 'string';
						break;
					}
					
					//Symbols
					$isSymbol = in_array(ord($c), self::$symbols);
					if ($isSymbol) {
						//Mark the buffer as being a symbol and to be wrapped up immediately,
						//since we want symbols to be separate tokens, not clumped together.
						$newBufferType = 'symbol';
						$wrapUpAnyway = true;
						
						//Check whether the symbol would make a valid symbol combination with
						//what's already in the buffer, in which case we leave the symbols
						//clumped together.
						$lookaheadBuffer = $buffer . $c;
						if (in_array($lookaheadBuffer, self::$symbolCombinations)) {
							$wrapUpAnyway = false;
						}
						break;
					}
					
					//Numbers
					if (ord($c) >= 0x30 && ord($c) <= 0x39) {
						$newBufferType = 'numeric';
						break;
					}
					
					//Identifiers (anything but the above and whitespaces)
					if ($c != null && strchr(" \t\n\r", $c) === false) {
						$newBufferType = 'identifier';
						break;
					}
				} break;
				
				//Inside comments.
				case 'comment.line': {
					if ($c == "\n")
						$context = 'code';
				} break;
				case 'comment.block': {
					if ($pc == '*' && $c == '/')
						$context = 'code';
				} break;
				
				//Inside strings.
				case 'string': {
					//Check whether we've reached the end of the string in which case we switch
					//back to code context. We leave new buffer kind invalid so the token gets
					//wrapped up.
					if ($ppc != '\\' && $pc != '\\' && $c == '"') {
						$context = 'code';
					}
					
					//Otherwise we mark this character as part of a string.
					else {
						$newBufferType = 'string';
					}
				} break;
			}
			
			//Numeric tokens are allowed inside an identifier.
			if ($bufferType == 'identifier' && $newBufferType == 'numeric') {
				$newBufferType = $bufferType;
			}
			
			//Numeric buffers suck up all identifiers and some symbol tokens.
			if ($bufferType == 'numeric') {
				if ($newBufferType == 'identifier' || $c == '.' ||
					(strchr("eE", $pc) !== false && strchr("+-", $c) !== false)) {
					$newBufferType = $bufferType;
					$wrapUpAnyway = false;
				}
			}
			
			//If the current and new buffer types disagree, we have to wrap up the current
			//buffer.
			if (($bufferType != $newBufferType || $wrapUpAnyway) && $buffer != '') {
				
				//If the current token is a symbol and it closes the topmost group on the stack,
				//remove the group and ignore the symbol.
				if ($bufferType == 'symbol' && $buffer == $groupStack[0]->closingSymbol()) {
					array_shift($groupStack);
				}
				
				//Otherwise we create a new node for this token.
				else {
					//If this is a bracket symbol, create a new group token.
					if ($bufferType == 'symbol' && strchr("({[", $buffer) !== false) {
						$subtypes = array('(' => '()', '{' => '{}', '[' => '[]');
						$n = new Group('group', clone $bufferRange, $subtypes[$buffer]);
					} else {
						$n = new Token($bufferType, clone $bufferRange, $buffer);
						
						//Potentially turn the token into a keyword.
						if (in_array($n->text, self::$keywords)) {
							$n->type = 'keyword';
						}
					}
					
					//Add the node to the topmost group.
					$groupStack[0]->children[] = $n;
					
					//If the new node is a group, add it to the top of the stack.
					if ($n instanceof Group) {
						array_unshift($groupStack, $n);
					}
				}
				
				//Clear the buffer and buffer type.
				$buffer     = '';
				$bufferType = null;
			}
			
			//If the current token is valid, append it to the buffer.
			if ($newBufferType != null) {
				if ($bufferType == null) {
					$bufferRange->start = clone $loc;
				}
				$bufferType = $newBufferType;
				$buffer .= $c;
			}
			
			//Increase the location column counter.
			$loc->column++;
			$loc->offset++;
			
			//Adjust the buffer range's end.
			$bufferRange->end = clone $loc;
		}
	}
}

/** Describes the location of a token through the start and end line and column. */
class Location
{
	public $line   = 1;
	public $column = 0;
	public $offset = 0;
}
class Range
{
	public $file;
	public $start;
	public $end;
	
	public function __toString() {
		$s = $this->file.':';
		$s .= $this->start->line.'.'.$this->start->column;
		$s .= '-';
		if ($this->start->line != $this->end->line)
			$s .= $this->end->line.'.';
		$s .= $this->end->column;
		return $s;
	}
}

/** Basic lexer node. */
class Node
{
	public $type;
	public $range;
	public function __construct($type, $range) {
		$this->type  = $type;
		$this->range = $range;
	}
	
	//Convenience.
	public function is($type)      { return $this->type == $type; }
	public function isIdentifier() { return $this->is('identifier'); }
	public function isKeyword($text = null) {
		return $this->is('keyword') && (!$text || $this->text == $text);
	}
	public function isSymbol()     { return $this->is('symbol'); }
	public function isNumeric()    { return $this->is('numeric'); }
	public function isString()     { return $this->is('string'); }
	public function isGroup($subtype = null) {
		return $this->is('group') && (!$subtype || $this->subtype == $subtype);
	}
}

/** Group node. */
class Group extends Node
{
	public $subtype;
	public $children;
	
	public function __construct($type, $range, $subtype) {
		parent::__construct($type, $range);
		$this->subtype = $subtype;
		$this->children = array();
	}
	
	public function openingSymbol() {
		return ($this->subtype == 'root' ? null : $this->subtype[0]);
	}
	public function closingSymbol() {
		return ($this->subtype == 'root' ? null : $this->subtype[1]);
	}
	
	public function desc($depth = -1, $indent = 0) {
		$break = "\n".str_repeat('    ', max($indent - 1, 0));
		$descChildren = ($depth > 0 || $depth == -1);
		$s = '';
		$afterBreak = false;
		if ($this->subtype != 'root') {
			$os = $this->openingSymbol();
			$s .= $os;
			if ($os == '{' && $descChildren) {
				$s .= $break;
				$afterBreak = true;
			} else {
				$s .= ' ';
			}
		}
		if ($descChildren) {
			foreach ($this->children as $c) {
				if ($afterBreak && $this->subtype != 'root') {
					$s .= '    ';
					$afterBreak = false;
				}
				$s .= $c->desc($depth == -1 ? -1 : $depth - 1, $indent + 1);
				if (($c->type == 'symbol' && $c->text == ';') || ($c->type == 'group' && $c->subtype == '{}')) {
					$s .= $break;
					$afterBreak = true;
				} else {
					$s .= " ";
				}
			}
		} else {
			$s .= '... ';
		}
		if ($this->subtype != 'root')
			$s .= $this->closingSymbol();
		return $s;
	}
}

/** Token node. */
class Token extends Node
{
	public $text;
	public function __construct($type, $range, $text) {
		parent::__construct($type, $range);
		$this->text = $text;
	}
	public function desc() {
		switch ($this->type) {
			case 'identifier': {
				return $this->text;
			} break;
			case 'keyword': {
				return keyword($this);
			} break;
			case 'symbol': {
				return $this->text;
			} break;
			case 'numeric': {
				return numeric($this);
			} break;
			case 'string': {
				return string($this);
			} break;
		}
		return $this->type.'?'.$this->text;
	}
}

//Initialize the lexer symbols.
Lexer::$symbols = array_merge(
	range(0x21, 0x2F),
	range(0x3A, 0x3F),
	range(0x5B, 0x5E),
	range(0x7B, 0x7E)
);
