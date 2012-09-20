<?php
namespace Analysis\Node;

/** Analysis information for expressions in general. */
class Expr extends Node
{
	public $type;
	
	public function __construct()
	{
		$this->type = new \Analysis\Type;
	}
}