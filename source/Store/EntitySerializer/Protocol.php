<?php
namespace Store\EntitySerializer;

/** Stores generic information on how to serialize entities. */
class Protocol
{
	protected $schemes;
	
	public function __construct()
	{
		$this->schemes = array();
		
		$this->register("FunctionDefinition", "function", array("&name", "&packageName", "@inputArgs", "@outputArgs", "@body", "@scope", "@innerScope"));
		$this->register('Func\Tuple', "func-tuple");
		$this->register('Func\Argument', "func-arg", array("&name", "@type", "@scope"));
		$this->register("TypeDefinition", "type", array("&name", "&packageName", "@scope"));
		$this->register("ExternalDeclaration", "external", array("&name", "@scope"));
		
		$this->register('Type\Member', "type-member", array("&name", "@type", "*scope"));
		
		//Statements
		$this->register("Block", "block", array("@headScope", "*tailScope"));
		$this->register('Stmt\Expr', "expr-stmt", array("@expr"));
		$this->register('Stmt\IfStmt', "if", array("@condition", "@body", "@else", "@scope"));
		$this->register('Stmt\ElseStmt', "else", array("@body", "@scope"));
		
		//Expressions
		$this->register('Expr\VarDef', "var", array("&name", "@type", "@initial", "@scope"));
		$this->register('Expr\Type', "type-expr", array("@expr"));
		$this->register('Expr\Identifier', "identifier", array("&name", "*scope"));
		$this->register('Expr\Constant', "constant", array("&type", "&value", "*scope"));
		$this->register('Expr\Operator\Binary', "binary-op", array("&operator", "@LHS", "@RHS"));
		$this->register('Expr\Operator\Unary', "unary-op", array("&operator", "@operand"));
		$this->register('Expr\NewOp', "new", array("@type"));
		$this->register('Expr\MemberAccess', "member-access", array("@expr", "&name"));
		$this->register('Expr\Call', "call", array("@callee", "@args"));
		$this->register('Expr\Call\Tuple', "call-tuple");
		$this->register('Expr\Call\Argument', "call-arg", array("@expr", "&name"));
		$this->register('Expr\Call\Callee', "call-callee", array("@expr"));
		$this->register('Expr\NativeType', "native-type", array("&name"));
		$this->register('Expr\ElementAccess', "element-access", array("@expr", "@index"));
		
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
	
	public function getClassForTagName($tagName)
	{
		foreach ($this->schemes as $s) {
			if ($s->tagName == $tagName)
				return $s->className;
		}
		return null;
	}
	
	protected function register($className, $tagName, array $fields = array())
	{
		$s = new CodingScheme("\\Entity\\$className", $tagName, $fields);
		$this->schemes[] = $s;
		return $s;
	}
}