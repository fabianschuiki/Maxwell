<?php
namespace C;

class Func extends Node
{
	public $signature;
	public $body;
	
	public function __construct()
	{
		$this->body = new Block;
	}
	
	public function getSignature()
	{
		return $this->signature;
	}
	
	public function getDefinition()  { return $this->getSignature()."\n{\n".static::indent($this->body->getCode())."\n}"; }
	public function getDeclaration() { return $this->getSignature().";"; }
}