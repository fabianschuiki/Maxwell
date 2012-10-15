<?php
namespace Store\EntitySerializer;

/** Stores generic information on how to serialize entities. */
class Protocol
{
	protected $schemes;
	
	public function __construct()
	{
		$this->schemes = array();
		
		$this->register("FunctionDefinition", "function", array("&name", "@body", "@scope"));
		$this->register("TypeDefinition", "type", array("&name", "@scope"));
		
		//Statements
		$this->register("Block", "block", array("@headScope", "*tailScope"));
		$this->register('Stmt\Expr', "expr-stmt", array("@expr"));
		
		//Expressions
		$this->register('Expr\VarDef', "var", array("&name", "@type", "@initial", "@scope"));
		$this->register('Expr\Type', "type-expr", array("@expr"));
		$this->register('Expr\Identifier', "identifier", array("&name", "@scope"));
		$this->register('Expr\Constant', "constant", array("&type", "&value"));
		$this->register('Expr\Operator\Binary', "binary-op", array("&operator", "@LHS", "@RHS"));
		$this->register('Expr\NewOp', "new", array("@type"));
		$this->register('Expr\MemberAccess', "member-access", array("@expr", "&name"));
		
		//Scope
		$this->register('Scope\Scope', "scope", array("*upper", "*outer"));
		$this->register('Scope\ScopeDeclaration', "scope-declaration", array("*declares"));
		$this->register('Scope\ScopeRoot', "scope-root", array("*rootEntity"));
	}
	
	public function getMainScheme(\Entity\Node $node)
	{
		foreach ($this->schemes as $s) {
			if ("\\".get_class($node) == $s->className)
				return $s;
		}
		return null;
	}
	
	public function getSchemes(\Entity\Node $node)
	{
		$schemes = array();
		foreach ($this->schemes as $s) {
			if ($node instanceof $s->className)
				$schemes[] = $s;
		}
		return $schemes;
	}
	
	protected function register($className, $tagName, array $fields = array())
	{
		$s = new CodingScheme("\\Entity\\$className", $tagName, $fields);
		$this->schemes[] = $s;
		return $s;
	}
}