<?php

class Scope
{
	static private $currentIndex = 0;
	
	public $parent;
	public $names = array();
	public $index;
	
	public function __construct($parent = null)
	{
		$this->parent = $parent;
		$this->index = static::$currentIndex++;
	}
	
	public function find($name)
	{
		$name = strval($name);
		if (isset($this->names[$name])) {
			$v = $this->names[$name];
			if ($v->kind == 'a.funcgrp') {
				if ($this->parent) {
					$v = array_merge($this->parent->find($name), $v->funcs);
				} else {
					$v = $v->funcs;
				}
			}
			return $v;
		}
		if ($this->parent) {
			return $this->parent->find($name);
		}
		return null;
	}
	
	public function add(IssueList $issues, Node $n)
	{
		$name = strval($n->name);
		
		//Check whether there's an existing entry with this name.
		if (isset($this->names[$name])) {
			$existing = $this->names[$name];
		} else {
			$existing = null;
		}
		
		//Functions need special treatment.
		if ($n->kind == 'def.func') {
			$grp = $existing;
			if (!$grp) {
				$grp = new Node;
				$grp->kind = 'a.funcgrp';
				$grp->name = $name;
				$grp->funcs = array();
				$this->names[$name] = $grp;
			}
			if ($grp->kind != 'a.funcgrp') {
				$issues[] = new Issue(
					'error',
					"Function '$name' cannot be defined since the name already exists.",
					$n->name->range,
					array($grp->name->range)
				);
				return;
			}
			$grp->funcs[] = $n;
		}
		
		//Other nodes are simple.
		else {
			if ($existing) {
				$issues[] = new Issue(
					'error',
					"'{$n->name}' is already defined.",
					$n->name->range,
					array($existing->name->range)
				);
				return;
			}
			$this->names[$name] = $n;
		}
	}
}
