<?php
namespace Entity\Expr;
use Entity\Scope\Scope;
use Entity\Scope\ScopeDeclaration;
use Source\Range;

class VarDef extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\VarDef $def)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($def->getRange());
		$e->setHumanRange($def->getName()->getRange());
		$e->setName($def->getName()->getText());
		if ($def->getType()) $e->setType(Type::makeFromSyntaxNode($def->getType()));
		if ($def->getInitial()) $e->setInitial(Expr::makeFromSyntaxNode($def->getInitial()));
		return $e;
	}
	
	public $compiler;
	
	public function __construct()
	{
		parent::__construct();
		$this->compiler = \Compiler\Node\Node::makeForEntity($this);
	}
	
	protected $name;
	protected $type;
	protected $initial;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setType(Type $t) { $this->type = $t; }
	public function getType() { return $this->type; }
	
	public function setInitial(Expr $i) { $this->initial = $i; }
	public function getInitial() { return $this->initial; }
	
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		if ($this->type) $this->type->initScope($scope);
		if ($this->initial) $this->initial->initScope($scope);
		
		$s = new ScopeDeclaration;
		$s->generateID();
		$s->setUpper($scope);
		$s->setDeclares($this);
		$scope = $s;
		$this->setScope($s);
	}
	
	public function getChildEntities()
	{
		return array_filter(array($this->type, $this->initial));
	}
}