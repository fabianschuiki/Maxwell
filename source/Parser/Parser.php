<?php
namespace Parser;
use AST;
use Lexer\Token;
use Lexer\TokenGroup;
use Lexer\TokenList;
use IssueList;
use Language;

class Parser
{
	protected $tokens;
	protected $nodes;
	
	public function __construct(TokenList $tokens)
	{
		$this->tokens = $tokens;
	}
	
	public function run()
	{
		$ids = new \IDProvider;
		$ids->push();
		
		$nodes = array();
		$tokens = $this->tokens->getStripped();
		while (!$tokens->isEmpty()) {
			$stmt = StatementParser::parseStmt($tokens);
			if ($stmt) $nodes[] = $stmt;
		}
		$this->nodes = $nodes;
		
		$ids->pop();
	}
	
	public function getNodes() { return $this->nodes; }
}