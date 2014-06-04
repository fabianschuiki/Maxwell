<?php
namespace LET;

class Ident_AST extends Ident
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\IdentExpr $node)
	{
		parent::__construct();
		$this->asn   = $node;
		$this->scope = $scope;
	}
	
	public function name()  { return $this->asn->name->text; }
	public function range() { return $this->asn->range(); }
}