<?php
namespace CET;

abstract class Node
{
	static public function make(\LET\Node $node, array &$cet)
	{
		if ($node instanceof \LET\ConcreteType_AST) return $cet[$node->id] = new Type($node, $cet);
		if ($node instanceof \LET\Func_AST)         return $cet[$node->id] = new Func($node, $cet);
		if ($node instanceof \LET\TypeMember_AST)   return $cet[$node->id] = new TypeMember($node, $cet);
		if ($node instanceof \LET\Variable)         return $cet[$node->id] = new Variable($node, $cet);
		if ($node instanceof \LET\Call)             return $cet[$node->id] = new Call($node, $cet);
		if ($node instanceof \LET\Member)           return $cet[$node->id] = new Member($node, $cet);
		if ($node instanceof \LET\Constant)         return $cet[$node->id] = new Constant($node, $cet);
		if ($node instanceof \LET\Ident)            return $cet[$node->id] = new Ident($node, $cet);
		\mwc\Compiler::error("unable to create CET node for ".get_class($node));
	}
	
	public function __construct()
	{
	}
	
	public function desc()
	{
		return get_class($this)." ".$this->details();
	}
	abstract function details();
}