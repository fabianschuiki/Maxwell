<?php
namespace LET;

class FuncType extends Type
{
	public $in;
	public $out;
	
	public function __construct(Scope $scope, TypeTuple $in, TypeTuple $out)
	{
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
	
	public function children() { return array($this->in, $this->out); }
}