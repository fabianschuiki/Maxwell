<?php
namespace LET;

class FuncType extends Type
{
	public $in;
	public $out;
	
	public function __construct(Scope $scope, Type $in, Type $out)
	{
		if (!$in  instanceof GenericType && !$in  instanceof TypeTuple) $in  = new TypeTuple($scope, array($in));
		if (!$out instanceof GenericType && !$out instanceof TypeTuple) $out = new TypeTuple($scope, array($out));
		
		$this->in    = $in;
		$this->out   = $out;
		$this->scope = $scope;
	}
	
	public function in()  { return $this->in;  }
	public function out() { return $this->out; }
	
	public function details()
	{
		$in = $this->in;
		if ($in) $in = $in->details();
		
		$out = $this->out;
		if ($out) $out = $out->details();
		
		return "$in -> $out";
	}
	
	public function children()   { return array($this->in, $this->out); }
	public function isSpecific() { return $this->in->isSpecific() && $this->out->isSpecific(); }
	
	public function reduceToAbsolute(Scope $scope)
	{
		return new FuncType($scope, $this->in->reduceToAbsolute($scope), $this->out->reduceToAbsolute($scope));
	}
}