<?php

class TypeSet extends Type
{
	public $any = true;
	public $types = array();
	
	public function __toString()
	{
		if ($this->any) {
			return 'any';
		}
		return '{'.implode(', ', $this->types).'}';
	}
	
	public function __construct()
	{
		foreach (func_get_args() as $t) {
			$this->addType($t);
		}
	}
	
	public function addType($type)
	{
		if ($type instanceof NamedType && $type->name == 'any') {
			$this->any = true;
			$this->types = array();
			return;
		}
		
		$this->any = false;
		$found = false;
		foreach ($this->types as $t) {
			if ($t->name == $type->name) {
				$found = true;
				break;
			}
		}
		if (!$found) {
			$this->types[] = $type;
		}
		usort($this->types, function($a,$b){
			if ($a->cost() > $b->cost()) return 1;
			if ($a->cost() < $b->cost()) return -1;
			return 0;
		});
	}
	
	public function addNativeType($type)
	{
		$this->addType(new NamedType(strval($type)));
	}
	
	public function addNativeTypes(array $types)
	{
		foreach ($types as $type) {
			$this->addNativeType($type);
		}
	}
	
	public function findCastTypes(Scope &$scope)
	{
		//Find the cast functions.
		$casts = $scope->find('cast');
		if (!is_array($casts))
			return;
		$casts = array_filter($casts, function($cast){
			return (count($cast->in) == 1 && count($cast->out) == 1 && strcmp($cast->in[0]->type, $cast->out[0]->type) != 0);
		});
		
		//Iterate through the native types and find available casts.
		foreach ($this->types as $type) {
			if ($type->cast) continue;
			
			//Create the initial search lead.
			$initial = new stdClass;
			$initial->name = $type->name;
			$initial->used = array();
			$initial->left = $casts;
			$leads = array($initial);
			
			//As long as we have leads to inspect, keep going.
			while (count($leads)) {
				$newLeads = array();
				foreach ($leads as $lead) {
					foreach ($lead->left as $cast) {
						if (strval($cast->in[0]->type) != $lead->name) continue;
						$new = clone $lead;
						$new->name = strval($cast->out[0]->type);
						$new->used[] = $cast;
						$new->left = array_filter($new->left, function($c) use ($cast) {
							return ($c != $cast);
						});
						
						//Create the new type.
						$t = new NamedType;
						$t->name = $new->name;
						$t->cast = $new->used;
						$this->addType($t);
						
						//If there are casts left to be tried, throw the new lead onto the stack.
						if (count($new->left)) {
							$newLeads[] = $new;
						}
					}
				}
				$leads = $newLeads;
			}
		}
	}
	
	public function types()
	{
		return array_filter($this->types, function($t){ return ($t->cost() == 0); });
	}
	
	public function unique()
	{
		$types = $this->types();
		if (count($types) == 1) {
			return $types[0];
		}
		return null;
	}
	
	public function match(Type $type, &$vars = array(), $initial = true)
	{
		if ($this->any) {
			return $type;
		}
		
		$match = new TypeSet;
		foreach ($this->types as $at) {
			$m = $at->match($type, $vars, false);
			if ($m) {
				if ($m instanceof TypeSet) {
					foreach ($m->types as $bt) {
						$match->addType($bt);
					}
				} else {
					$match->addType($m);
				}
			}
		}
		
		if ($initial) {
			$match->resolveVars();
		}
		
		if (count($match->types) > 1) {
			return $match;
		} else if (count($match->types) == 1) {
			return $match->types[0];
		}
		return null;
	}
	
	public function resolveVars()
	{
		for ($i = 0; $i < count($this->types); $i++) {
			$t = $this->types[$i];
			if ($t instanceof TypeVar) {
				$this->types[$i] = $t->type;
			} else {
				$t->resolveVars();
			}
		}
	}
	
	public function cost()
	{
		$min = null;
		foreach ($this->types as $t) {
			$c = $t->cost();
			if ($min === null || $c < $min) {
				$min = $c;
			}
		}
		return $min;
	}
}