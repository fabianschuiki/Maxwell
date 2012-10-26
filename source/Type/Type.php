<?php
namespace Type;

/** Base class for all type information. */
class Type
{
	static public function equal(Type $a, Type $b)
	{
		if ($a instanceof Builtin && $b instanceof Builtin) {
			return ($a->getName() == $b->getName());
		}
		if ($a instanceof Defined && $b instanceof Defined) {
			return ($a->getTypeDef()->getID() == $b->getTypeDef()->getID());
		}
		if ($a instanceof Generic && $b instanceof Generic) {
			return true;
		}
		return false;
	}
	
	public function toHumanReadableString()
	{
		if ($this instanceof Generic) return "generic";
		if ($this instanceof Builtin) return $this->getName();
		if ($this instanceof Defined) return $this->getDefinition()->getName();
		if ($this instanceof Func)    return $this->getInputArgs()->toHumanReadableString()." -> ".$this->getOutputArgs()->toHumanReadableString();
		if ($this instanceof Tuple) {
			$fields = array_map(function($f) { return $f->toHumanReadableString(); }, $this->getFields());
			return "(".implode(", ", $fields).")";
		}
		throw new \exception("Unable to convert ".vartype($this)." to human readable string.");
	}
}