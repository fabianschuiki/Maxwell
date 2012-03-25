<?php
namespace LET;

class FuncArg_AST extends FuncArg
{
	public $asn;
	
	public function __construct(\AST\FuncArg $node)
	{
		$this->asn = $node;
	}
	
	public function type() { return $this->asn->type->ident->text; }
	public function name() { return $this->asn->name->text; }
}