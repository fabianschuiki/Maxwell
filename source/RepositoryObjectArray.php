<?php
/* Copyright © 2013 Fabian Schuiki. */

class RepositoryObjectArray extends RepositoryNodeObject
{
	protected $elements = array();

	public function getClass() { return null; }

	public function getFragmentNames()
	{
		return array();
	}

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

	public function get($key)
	{
		// TODO: maybe some loading is necessary?
		if (!isset($this->elements[$key])) {
			throw new \InvalidArgumentException("Requested element $key does not exist.");
		}
		return $this->elements[$key];
	}

	public function getElements()
	{
		return $this->elements;
	}

	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;

	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
}