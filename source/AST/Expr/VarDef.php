<?php
namespace AST\Expr;
use Lexer\Token;

class VarDef extends Expr
{
	protected $type;
	protected $name;
	protected $initial;
	
	public function __construct(Expr $type = null, Token $name, Expr $initial = null)
	{
		parent::__construct();
		$this->type    = $type;
		$this->name    = $name;
		$this->initial = $initial;
	}
	
	public function getType()    { return $this->type; }
	public function getName()    { return $this->name; }
	public function getInitial() { return $this->initial; }
}