<?php
namespace Entity\Scope;

class Scope extends \Entity\Node
{
	protected $outer;
	protected $upper;
	
	public function setOuter(Scope $s = null) { $this->outer = $s; }
	public function getOuter() { return $this->outer; }
	
	public function setUpper(Scope $s = null) { $this->upper = $s; }
	public function getUpper() { return $this->upper; }
}