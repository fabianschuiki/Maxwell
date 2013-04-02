<?php
/* Copyright © 2013 Fabian Schuiki */

class RepositoryObjectReference implements RepositoryObjectParentInterface
{
	protected $repository;
	protected $id = null;
	protected $obj = null;
	protected $obj_dirty = false;

	protected $parent = null;
	protected $parent_fragment = null;

	public function __construct(Repository $repo)
	{
		$this->repository = $repo;
	}

	public function set($value)
	{
		if (is_object($value)) {
			$vid = $value->getId();
			if ($this->id !== $vid) {
				$this->id = $vid;
				$this->obj = $value;
				$this->obj_dirty = false;
				$this->println(1, "Set object {$this->id} directly");
				$this->notifyParent();
			}
		} else {
			if ($this->id !== $value) {
				$this->id = $value;
				$this->obj = null;
				$this->obj_dirty = true;
				$this->println(1, "Set ID {$this->id}, object invalidated");
				$this->notifyParent();
			}
		}
	}

	public function get()
	{
		if ($this->obj_dirty) {
			$this->obj_dirty = false;
			$this->println(0, "Resolving ID ".($this->id !== null ? $this->id : "<null>"));
			if ($this->id !== null) {
				$this->obj = $this->repository->getObject($this->id);
			} else {
				$this->obj = null;
			}
		}
		return $this->obj;
	}

	public function getId()
	{
		return $this->id;
	}

	public function describe()
	{
		$s  = "@ref ";
		if ($this->id === null) {
			$s .= "<null>";
		} else {
			$s .= $this->id." ".($this->obj_dirty ? "<unresolved>" : get_class($this->obj));
		}
		return $s;
	}

	public function setParent(RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_fragment = $fragment;
	}

	protected function notifyParent()
	{
		if ($this->parent) {
			$this->println(2, "Notifying parent {$this->parent->getId()} about change to fragment {$this->parent_fragment}");
			$this->parent->notifyFragmentDirty($this->parent_fragment);
		}
	}

	static public $verbosity = 0;
	private function println($verbosity, $ln)
	{
		if (static::$verbosity > $verbosity)
			Log::println($ln, get_class());
	}
}