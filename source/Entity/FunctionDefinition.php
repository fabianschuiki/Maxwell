<?php
namespace Entity;
use Source\Range;

class FunctionDefinition extends RootEntity
{
	static public function makeFromSyntaxNode(\AST\Stmt\FuncDef $def)
	{
		$e = new self;
		$e->generateID();
		$e->pushID();
		$e->setRange($def->getRange());
		$e->setHumanRange(Range::union($def->getKeyword()->getRange(), $def->getName()->getRange()));
		$e->setName($def->getName()->getText());
		if ($b = $def->getBody()) $e->setBody(Block::makeFromSyntaxNode($b));
		
		$ins = Func\Tuple::makeFromSyntaxNodes($def->getArgsIn());
		if (!$ins->getRange()) $ins->setRange($e->getHumanRange());
		$e->setInputArgs($ins);
		
		$outs = Func\Tuple::makeFromSyntaxNodes($def->getArgsOut());
		if (!$outs->getRange()) $outs->setRange($e->getHumanRange());
		$e->setOutputArgs($outs);
		
		$e->popID();
		return $e;
	}
	
	protected $name;
	protected $body;
	protected $scope;
	protected $inputArgs;
	protected $outputArgs;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setBody(Block $b = null) { $this->body = $b; }
	public function getBody() { return $this->body; }
	
	public function setScope(Scope\Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function setInputArgs(Func\Tuple $t) { $this->inputArgs = $t; }
	public function getInputArgs() { return $this->inputArgs; }
	
	public function setOutputArgs(Func\Tuple $t) { $this->outputArgs = $t; }
	public function getOutputArgs() { return $this->outputArgs; }
	
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
		$this->inputArgs->initScope($s);
		$this->outputArgs->initScope($s);
		if ($this->body) $this->body->initScope($s);
	}
	
	public function getChildEntities()
	{
		$a = array($this->inputArgs, $this->outputArgs);
		if ($this->body) $a[] = $this->body;
		return $a;
	}
}