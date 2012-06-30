<?php

class Lexer
{
	public $file;
	public $tokens;
	public $flatTokens;
	public $issues;
	
	public function run()
	{
		assert($this->file);
		$input = $this->file->content;
		
		$this->tokens = array();
		$this->flatTokens = array();
		$this->issues = array();
		
		//Accumulation buffer for tokens.
		$bufferType  = null;
		$bufferRange = new Range;
		$bufferRange->source = $this->file;
		$buffer      = "";
		
		//Location tracking.
		$loc = new Location;
		
		//Keep a group stack.
		$groupStack = array();
		
		//Iterate through every character in the input string.
		$context = 'code';
		$len = strlen($input);
		$pc = $c = 0;
		for ($i = 0; $i < $len + 1; $i++) {
			$ppc = $pc;
			$pc  = $c;
			$c   = ($i   < $len ? $input[$i]   : null);
			$nc  = ($i+1 < $len ? $input[$i+1] : null);
			
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
					$isSymbol = in_array(ord($c), Language::$symbols);
					if ($isSymbol) {
						//Mark the buffer as being a symbol and to be wrapped up immediately,
						//since we want symbols to be separate tokens, not clumped together.
						$newBufferType = 'symbol';
						$wrapUpAnyway = true;
						
						//Check whether the symbol would make a valid symbol combination with
						//what's already in the buffer, in which case we leave the symbols
						//clumped together.
						$lookaheadBuffer = $buffer . $c;
						if (in_array($lookaheadBuffer, Language::$symbolCombinations)) {
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
					if (($ppc == '\\' || $pc != '\\') && $c == '"') {
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
				
				//Buffer type alterations based on content.
				if (in_array($buffer, Language::$identifierSymbols)) {
					$bufferType = 'identifier';
				}
				if (in_array($buffer, Language::$keywords)) {
					$bufferType = 'keyword';
				}
				
				//Create the default token and add it to the flat token list.
				$dt = new Token;
				$dt->type  = $bufferType;
				$dt->range = clone $bufferRange;
				$dt->text  = $buffer;
				$this->flatTokens[] = $dt;
				
				//If the current token is a symbol and it closes the topmost group on the stack,
				//remove the group and ignore the symbol.
				if ($bufferType == 'symbol' && strchr(")}]", $buffer) !== false) {
					if (count($groupStack) > 0) {
						$style = $groupStack[0]->text;
						if ($style[1] != $buffer) {
							$this->issues[] = "$bufferRange: symbol $buffer doesn't close previous group $style properly";
						} else {
							$groupStack[0]->range->combine($bufferRange);
							array_shift($groupStack);
						}
					} else {
						$this->issues[] = "$bufferRange: symbol $buffer does not have a corresponding opening symbol";
					}
				}
				
				//Otherwise we create a new node for this token.
				else {
					//If this is a bracket symbol, create a new group token.
					if ($bufferType == 'symbol' && strchr("({[", $buffer) !== false) {
						$styles = array('(' => '()', '{' => '{}', '[' => '[]');
						$dt = new TokenGroup;
						$dt->type  = 'group';
						$dt->range = clone $bufferRange;
						$dt->text = $styles[$buffer];
					}
					
					//Add the node to the topmost group.
					if (count($groupStack) > 0) {
						$groupStack[0]->tokens[] = $dt;
					} else {
						$this->tokens[] = $dt;
					}
					
					//If the new node is a group, add it to the top of the stack.
					if ($dt->is('group')) {
						array_unshift($groupStack, $dt);
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
			if ($c == "\n") {
				$loc->line++;
				$loc->column = 0;
			} else {
				$loc->column++;
			}
			$loc->offset++;
			
			//Adjust the buffer range's end.
			$bufferRange->end = clone $loc;
		}
		
		foreach ($this->issues as $i) {
			echo $i."\n";
		}
	}
}
