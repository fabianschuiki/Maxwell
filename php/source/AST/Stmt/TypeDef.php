<?php
namespace AST\Stmt;
use Lexer\Token;
use AST\Block;

class TypeDef extends Keyword
{
	protected $name;
	protected $superType;
	protected $body;
	
	public function __construct(Token $keyword, Token $name, Token $superType = null, Block $body)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->name = $name;
		$this->superType = $superType;
		$this->body = $body;
	}
	
	public function getName() { return $this->name; }
	public function getSuperType() { return $this->superType; }
	public function getBody() { return $this->body; }
}