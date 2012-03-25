<?php
namespace AST;

class MemberExpr extends Expr
{
	public $expr;
	public $dot;
	public $member;
	
	public function __construct(Expr $expr, \Token $dot, \Token $member)
	{
		assert($dot->is('symbol', '.'));
		assert($member->is('identifier'));
		
		$this->expr   = $expr;
		$this->dot    = $dot;
		$this->member = $member;
	}
}