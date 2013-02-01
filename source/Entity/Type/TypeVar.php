<?php
namespace Entity\Type;
use Entity\Expr\Type;
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
		return $e;
	}
	
	/*public $analysis;
	public $compiler;
	
	public function __construct()
	{
		$this->analysis = \Analysis\Node\Node::makeForEntity($this);
		$this->compiler = \Compiler\Node\Node::makeForEntity($this);
	}*/
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	
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
		return $e;
	}
}