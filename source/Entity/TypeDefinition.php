<?php
namespace Entity;
use Source\Range;
use Lexer\Token;
use IssueList;

class TypeDefinition extends RootEntity
{
	static public function makeFromSyntaxNode(\AST\Stmt\TypeDef $def)
	{
		$e = new self;
		$e->generateID();
		$e->pushID();
		$e->setRange(Range::union($def->getKeyword()->getRange(), $def->getBody()->getRange()));
		
		if ($def->getSuperType())
			$hr = $def->getSuperType();
		else
			$hr = $def->getName();
		$e->setHumanRange(Range::union($def->getKeyword()->getRange(), $hr->getRange()));
		
		$e->setName($def->getName()->getText());
		if ($def->getSuperType())
			$e->setSuperType($def->getSuperType()->getText());
		
		//Disassemble the body containing the members.
		$members = array();
		$typeVars = array();
		foreach ($def->getBody()->getStmts() as $stmt) {
			if ($stmt instanceof \AST\Stmt\Expr) {
				$expr = $stmt->getExpr();
				if ($expr instanceof \AST\Expr\VarDef) {
					$members[] = Type\Member::makeFromSyntaxNode($expr);
				}
				else if ($expr instanceof \AST\Expr\TypeVar) {
					$typeVars[] = Type\TypeVar::makeFromSyntaxNode($expr);
					//IssueList::add('warning', "Ignoring type variable '{$expr->getName()->getText()}' as they are not yet implemented.", $expr);
				}
				else {
					throw new \exception(vartype($expr)." makes no sense as a statement inside a type definition. Replace this with a proper issue!");
				}
			}
			else {
				throw new \exception(vartype($stmt)." not allowed inside type definition. Replace this with a proper issue!");
			}
		}
		$e->setMembers($members);
		$e->setTypeVars($typeVars);
		
		$e->popID();
		return $e;
	}
	
	protected $name;
	protected $superType;
	protected $members;
	protected $typeVars;
	protected $scope;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setSuperType($s) { $this->superType = $s; }
	public function getSuperType() { return $this->superType; }
	
	public function setMembers(array $m) { $this->members = $m; }
	public function getMembers() { return $this->members; }

	public function setTypeVars(array $t) { $this->typeVars = $t; foreach ($t as $tv) $tv->setParent($this); }
	public function getTypeVars() { return $this->typeVars; }
	
	public function setScope(Scope\Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope\Scope $scope = null)
	{
		if ($scope) {
			$s = new Scope\ScopeDeclaration;
			$s->setUpper($scope);
			$s->setDeclares($this);
		} else {
			$s = new Scope\ScopeRoot;
			$s->setRootEntity($this);
		}
		$s->generateID();
		$this->setScope($s);
		foreach ($this->members as $member) {
			$member->initScope($s);
		}
		foreach ($this->typeVars as $typeVar) {
			$typeVar->initScope($s);
		}
	}
	
	public function getChildEntities() { return array_merge($this->members, $this->typeVars); }
}