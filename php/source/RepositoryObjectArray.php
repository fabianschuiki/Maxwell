<?php
/* Copyright © 2013 Fabian Schuiki. */

class RepositoryObjectArray extends RepositoryNodeObject implements EqualInterface
{
	protected $elements = array();

	public function getClass() { return null; }

	public function getFragmentNames() { return array(); }
	public function getFragment($fragment) { throw new \RuntimeException("getFragment() should never be called on arrays"); }

	public function set($key, RepositoryNodeObject $object)
	{
		if (isset($this->elements[$key]) && $this->elements[$key] !== null) {
			$this->elements[$key]->setParent(null);
		}
		$this->elements[$key] = $object;
		if ($object !== null) {
			$object->setParent($this, $key, "tree");
		}
	}

	public function add(RepositoryNodeObject $object)
	{
		$i = count($this->elements);
		while (isset($this->elements[$i])) $i++;
		$this->set($i, $object);
	}

	public function get($key, $enforce = false)
	{
		// TODO: maybe some loading is necessary?
		if (!isset($this->elements[$key])) {
			if ($enforce)
				throw new \InvalidArgumentException("Requested element $key does not exist.");
			else
				return null;
		}
		return $this->elements[$key];
	}

	public function getElements()
	{
		return $this->elements;
	}
	
	public function getChildren()
	{
		return $this->elements;
	}

	public function getCount()
	{
		return count($this->elements);
	}

	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;

	public function setParent(IdedObject $parent = null, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}

	public function describe($header = true)
	{
		$s  = ($header ? $this->getId()." " : "");
		$s .= "[\n";
		foreach ($this->getElements() as $index => $element) {
			if ($element === null) continue;
			$s .= "   [$index] ";
			$s .= str_replace("\n", "\n   ", $element->describe(false));
			$s .= "\n";
		}
		$s .= "]";
		return $s;
	}

	public function isEqualTo($x)
	{
		if (count($this->elements) != count($x->elements))
			return false;
		foreach ($this->elements as $index => $element) {
			if (!isset($x->elements[$index]))
				return false;
			if (!$this->areEqual($element, $x->elements[$index]))
				return false;
		}
		return true;
	}
}