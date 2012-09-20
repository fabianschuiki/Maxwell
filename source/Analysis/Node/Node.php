<?php
namespace Analysis\Node;

/** Root class for analysis nodes assigned to entities. */
class Node
{
	static public function makeForEntity(\Entity\Entity $e)
	{
		if ($e instanceof \Entity\Expr\Identifier) return new Identifier;
		if ($e instanceof \Entity\Expr\Expr) return new Expr;
		throw new \exception("No analysis node exists for ".vartype($e));
	}
}