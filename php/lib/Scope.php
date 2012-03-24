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
				$pv = null;
				if ($this->parent) {
					$pv = $this->parent->find($name);
				}
				if ($pv) {
					$v = array_merge($pv, $v->funcs);
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
		if (!$n->name) {
			return;
		}
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
	
	public function serialize()
	{
		$lines = array();
		foreach ($this->names as $name => $node) {
			$lines[] = "$name: ".$this->serializeNode($node);
		}
		return implode("\n", $lines);
	}
	
	private function serializeNode(Node $node)
	{
		switch ($node->kind) {
			case 'a.funcgrp': {
				$funcs = array();
				foreach ($node->funcs as $func) {
					$funcs[] = $func->c_name.':'.$this->serializeType($func->a_types);
				}
				return 'f'.count($funcs).':'.implode('', $funcs);
			} break;
			case 'def.type': {
				$members = array();
				foreach ($node->nodes as $member) {
					switch ($member->kind) {
						case 'expr.var': {
							$members[] = 'v'.$member->name.':'.$this->serializeType($member->a_types);
						} break;
					}
				}
				return 't'.$node->c_name.':'.count($members).':'.implode('', $members);
			} break;
		}
		return null;
	}
	
	private function serializeType(Type $type)
	{
		switch (get_class($type)) {
			case 'FuncType': {
				return '@f'.$this->serializeType($type->in).$this->serializeType($type->out);
			} break;
			case 'TupleType': {
				$fields = array();
				foreach ($type->fields as $field) {
					$fields[] = $field->name.':'.$this->serializeType($field->type);
				}
				return '@t'.count($fields).':'.implode('', $fields);
			} break;
			case 'NamedType': {
				return '@n'.$type->name.';';
			} break;
			case 'TypeVar': {
				return '@v'.$type->name.';';
			} break;
		}
		return null;
	}
	
	static public function unserialize($str)
	{
		$scope = new Scope;
		$lines = explode("\n", str_replace(array("\t", ' '), '', $str));
		foreach ($lines as $line) {
			list($name, $obj) = explode(':', $line, 2);
			$scope->names[$name] = static::unserializeNode($name, $obj);
		}
		return $scope;
	}
	
	static private function unserializeNode($name, $str, &$i = 0)
	{
		//echo "unserialize node: ".substr($str, $i)."\n";
		$type = $str[$i++];
		switch ($type) {
			case 'f': {
				$col = strpos($str, ':', $i);
				$count = substr($str, $i, $col-$i);
				$i = $col+1;
				$grp = new Node;
				$grp->kind = 'a.funcgrp';
				$grp->funcs = array();
				for ($n = 0; $n < $count; $n++) {
					$col = strpos($str, ':', $i);
					$c_name = substr($str, $i, $col-$i);
					$i = $col+1;
					$func = new Node;
					$func->kind = 'def.func';
					$func->name = $name;
					$func->c_name = $c_name;
					$func->a_types = static::unserializeType($str, $i);
					if (count($func->a_types->out->fields)) {
						$func->c_retname = "{$func->c_name}_t";
					} else {
						$func->c_retname = null;
					}
					$grp->funcs[] = $func;
				}
				return $grp;
			} break;
			case 't': {
				$col = strpos($str, ':', $i);
				$c_name = substr($str, $i, $col-$i);
				$i = $col+1;
				$col = strpos($str, ':', $i);
				$count = substr($str, $i, $col-$i);
				$i = $col+1;
				$def = new Node;
				$def->kind = 'def.type';
				$def->name = $name;
				$def->c_name = $c_name;
				$def->a_scope = new Scope;
				for ($n = 0; $n < $count; $n++) {
					$member_type = $str[$i++];
					switch ($member_type) {
						case 'v': {
							$col = strpos($str, ':', $i);
							$member_name = substr($str, $i, $col-$i);
							$i = $col+1;
							$member = new Node;
							$member->kind = 'expr.var';
							$member->name = $member_name;
							$member->c_name = Compiler::makeCIdent($member->name);
							$member->c_ref = $member->c_name;
							$member->a_types = static::unserializeType($str, $i);
							$def->a_scope->names[$member_name] = $member;
						} break;
					}
				}
				return $def;
			} break;
		}
		return null;
	}
	
	static private function unserializeType($str, &$i = 0)
	{
		//echo "unserialize type: ".substr($str, $i)."\n";
		assert($str[$i++] == '@');
		$type = $str[$i++];
		switch ($type) {
			case 'f': {
				$t = new FuncType;
				$t->in  = static::unserializeType($str, $i);
				$t->out = static::unserializeType($str, $i);
				$t->out->strict = false;
				return $t;
			} break;
			case 't': {
				$col = strpos($str, ':', $i);
				$count = substr($str, $i, $col-$i);
				$i = $col+1;
				$t = new TupleType;
				for ($n = 0; $n < $count; $n++) {
					$col = strpos($str, ':', $i);
					$name = substr($str, $i, $col-$i);
					$i = $col+1;
					if (!strlen($name)) {
						$name = null;
					}
					$t->addField(static::unserializeType($str, $i), $name);
				}
				return $t;
			} break;
			case 'n': {
				$sem = strpos($str, ';', $i);
				$name = substr($str, $i, $sem-$i);
				$i = $sem+1;
				$t = new NamedType;
				$t->name = $name;
				$i += $count;
				return $t;
			} break;
		}
		return null;
	}
}
