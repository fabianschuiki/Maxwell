<?php
namespace AST\Expr;
use AST\Node;

abstract class Expr extends Node
{
	public function __construct()
	{
		parent::__construct();
	}
}