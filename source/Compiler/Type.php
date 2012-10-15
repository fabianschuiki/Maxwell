<?php
namespace Compiler;

/** Holds all compiler-specific type information of an entity, like the C type name and
 * whether this is a pointer. */
class Type
{
	protected $name;
	protected $pointerLevel;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setPointerLevel($p) { $this->pointerLevel = $p; }
	public function getPointerLevel() { return $this->pointerLevel; }
	
	public function getCType() { return $this->name.str_repeat("*", $this->pointerLevel); }
}