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
			return ($a->getDefinition()->getID() == $b->getDefinition()->getID());
		}
		if ($a instanceof Generic && $b instanceof Generic) {
			return true;
		}
		if ($a instanceof Func && $b instanceof Func) {
			return static::equal($a->getInputArgs(), $b->getInputArgs()) && static::equal($a->getOutputArgs(), $b->getOutputArgs());
		}
		if ($a instanceof Tuple && $b instanceof Tuple) {
			$fa = $a->getFields();
			$fb = $b->getFields();
			$n = count($fa);
			if (count($fb) != $n) return false;
			for ($i = 0; $i < $n; $i++) {
				if (!static::equal($fa[$i], $fb[$i]))
					return false;
			}
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