<?php
namespace Analysis\Node;

/** Root class for analysis nodes assigned to entities. */
class Node extends \Entity\Node
{
	static public function makeForEntity(\Entity\Entity $e)
	{
		$n = null;
		if ($e instanceof \Entity\Expr\Identifier) $n = new Identifier;
		else if ($e instanceof \Entity\Expr\Expr) $n = new Expr;
		
		if (!$n) throw new \exception("No analysis node exists for ".vartype($e));
		$n->generateId();
		return $n;
	}
}