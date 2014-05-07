<?php
namespace Entity\Type;
use Entity\Scope\Scope;

class TypeVar extends \Entity\Entity
{
	static public function makeFromSyntaxNode(\AST\Expr\TypeVar $typeVar)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($typeVar->getRange());
		$e->setHumanRange($typeVar->getName()->getRange());
		$e->setName($typeVar->getName()->getText());
		$e->setType(\Type\Generic::make());
		return $e;
	}
	
	public function __construct()
	{
		$this->type = null;
	}
	
	protected $name;
	protected $type;

	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }

	public function setType(\Type\Type $t) { $this->type = $t; }
	public function getType() { return $this->type; }
	
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		$this->setScope($scope);
	}
	
	public function getChildEntities() { return array(); }

	public function copy()
	{
		$e = new self;
		$e->generateID();
		$e->setRange($this->getRange());
		$e->setHumanRange($this->getHumanRange());
		$e->setName($this->name);
		if ($this->type) $e->setType($this->type->copy());
		return $e;
	}
}