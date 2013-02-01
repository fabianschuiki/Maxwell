<?php
namespace Entity\Type;
use Entity\Expr\Type;
use Entity\Scope\Scope;

class Member extends \Entity\Entity
{
	static public function makeFromSyntaxNode(\AST\Expr\VarDef $member)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($member->getRange());
		$e->setHumanRange($member->getName()->getRange());
		$e->setName($member->getName()->getText());
		if ($member->getType()) $e->setType(Type::makeFromSyntaxNode($member->getType()));
		return $e;
	}
	
	public $analysis;
	public $compiler;
	
	public function __construct()
	{
		$this->analysis = \Analysis\Node\Node::makeForEntity($this);
		$this->compiler = \Compiler\Node\Node::makeForEntity($this);
	}
	
	protected $name;
	protected $type;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setType(Type $t) { $this->type = $t; }
	public function getType() { return $this->type; }
	
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		if ($this->type) $this->type->initScope($scope);
		$this->setScope($scope);
	}
	
	public function getChildEntities()
	{
		$a = array();
		if ($this->type) $a[] = $this->type;
		return $a;
	}

	public function copy()
	{
		$e = new self;
		$e->generateID();
		$e->setRange($this->getRange());
		$e->setHumanRange($this->getHumanRange());
		$e->setName($this->getName());
		if ($this->getType()) $e->setType($this->getType()->copy());
		return $e;
	}
}