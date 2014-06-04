<?php
namespace AST\Stmt;
use Lexer\Token;
use Lexer\TokenGroup;

class External extends Keyword
{
	protected $name;
	protected $declarations;
	protected $group;
	
	public function __construct(Token $keyword, Token $name, array $declarations, TokenGroup $group, Token $semicolon = null)
	{
		parent::__construct();
		foreach ($declarations as $d) assert($d instanceof Stmt);
		$this->keyword = $keyword;
		$this->name = $name;
		$this->declarations = $declarations;
		$this->group = $group;
		$this->semicolon = $semicolon;
	}
	
	public function getName() { return $this->name; }
	public function getDeclarations() { return $this->declarations; }
	public function getGroup() { return $this->group; }
}