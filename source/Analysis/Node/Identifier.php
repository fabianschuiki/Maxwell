<?php
namespace Analysis\Node;

/** Analysis information for expressions in general. */
class Identifier extends Expr
{
	public $binding;
	
	public function __construct()
	{
		parent::__construct();
		$this->binding = new \Analysis\Binding;
	}
}