<?php
namespace Compiler\Node;

class VarDef extends Node
{
	public function __construct(\Entity\Expr\VarDef $entity)
	{
		parent::__construct($entity);
		//$this->type = new \Compiler\Type;
	}
	
	protected $name;
	protected $type;
	protected $refType;
	protected $cType;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setType(\Type\Type $t) { $this->type = $t; }
	public function getType() { return $this->type; }
	
	public function setRefType($t) { $this->refType = $t; }
	public function getRefType() { return $this->refType; }
	
	public function setCType($t) { $this->cType = $t; }
	public function getCType() { return $this->cType; }
	
	//TODO: change stuff so that this class has a public member "type" that points to a generic compiled type information structure.
	//public $type;
}