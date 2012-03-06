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
		$ts = implode(', ', $this->types);
		if (count($this->types) > 1) {
			$ts = '{'.$ts.'}';
		}
		return $ts;
	}
	
	public function __construct($type = null)
	{
		if ($type) {
			$this->addType($type);
		}
	}
	
	public function addType($type)
	{
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
		if ($type == 'any') {
			$this->any = true;
			$this->types = array();
			return;
		}
		$t = new NamedType;
		$t->name = strval($type);
		$this->addType($t);
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
	
	public function intersection(TypeSet $types)
	{
		$t = clone $this;
		if (!$t->intersect($types)) {
			return null;
		}
		return $t;
	}
	
	public function intersect(TypeSet $types)
	{
		if ($types->any) {
			return true;
		}
		if ($this->any) {
			$this->any = false;
			$this->types = $types->types;
			return true;
		}
		$this->types = array_filter($this->types, function($t) use($types) {
			foreach ($types->types as $st) {
				if ($t->matches($st)) {
					return true;
				}
			}
			return false;
		});
		return count($this->types) > 0;
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
	
	public function matches(Type $type)
	{
		if ($type instanceof TypeSet) {
			if ($this->any) {
				return true;
			}
			foreach ($type->types as $t) {
				if ($this->matches($t)) {
					return true;
				}
			}
		} else {
			if ($this->any) {
				return true;
			}
			foreach ($this->types as $t) {
				if ($t->matches($type)) {
					return true;
				}
			}
		}
		return false;
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