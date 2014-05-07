<?php
namespace AST\Expr;
use Lexer\TokenGroup;

class InlineMap extends Expr
{
	protected $pairs;
	protected $group;
	
	public function __construct(array $pairs, TokenGroup $group)
	{
		parent::__construct();
		foreach ($pairs as $p) assert($p instanceof InlineMapPair);
		$this->pairs = $pairs;
		$this->group = $group;
	}
	
	public function getPairs() { return $this->pairs; }
	public function getGroup() { return $this->group; }
}