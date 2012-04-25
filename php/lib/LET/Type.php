<?php
namespace LET;

abstract class Type extends Node
{
	/// If $expr is null, returns a GenericType. If $expr is either an AST\Expr or Expr, returns a TypeExpr. Otherwise returns null.
	static public function make(Scope $scope, $expr)
	{
		if ($expr) {
			if ($expr instanceof \AST\Expr) {
				$expr = Expr::make($scope, $expr);
			}
			if ($expr instanceof Expr) {
				return new TypeExpr($scope, $expr);
			}
		} else {
			return new GenericType($scope);
		}
		return null;
	}
	
	static public function equal($types)
	{
		if (!is_array($types)) $types = func_get_args();
		while (count($types) > 0) {
			$a = array_shift($types);
			foreach ($types as $b) if (!static::equalTwo($a, $b)) return false;
		}
		return true;
	}
	
	static public function equalTwo($a, $b)
	{
		if (!$a) return false;
		if (!$b) return false;
		assert($a instanceof Type && $b instanceof Type);
		
		if ($a instanceof FuncType && $b instanceof FuncType) {
			return (static::equalTwo($a->in(), $b->in()) && static::equalTwo($a->out(), $b->out()));
		}
		if ($a instanceof TypeTuple && $b instanceof TypeTuple) {
			if (array_keys($a->fields) != array_keys($b->fields)) return false;
			foreach ($a->fields as $name => $type) if (!static::equalTwo($type, $b->fields[$name])) return false;
			return true;
		}
		if ($a instanceof MemberConstrainedType && $b instanceof MemberConstrainedType) {
			if (!static::equalTwo($a->type, $b->type)) return false;
			if (array_keys($a->members) != array_keys($b->members)) return false;
			foreach ($a->members as $member => $type) if (!static::equalTwo($type, $b->members[$member])) return false;
			return true; 
		}
		return ($a == $b);
	}
	
	/// Finds the largest common type (set, tuple, etc.) among a number of types.
	static public function intersect($types)
	{
		$args = func_get_args();
		$scope = null;
		if (count($args) > 0) {
			$scope = array_pop($args);
			if (!$scope instanceof Scope) {
				array_push($args, $scope);
				$scope = null;
			}
		}
		if (!is_array($types)) $types = $args;
		if (count($types) == 0) return null;
		foreach ($types as $type) {
			if ($type) continue;
			//trigger_error("Intersect with null type!", E_USER_ERROR);
			throw new \RuntimeException("Intersect contains null: ".implode(', ', array_map(function($type){ return ($type ? $type->details() : 'null'); }, $types)));
			debug_backtrace();
		}
		//$types = array_filter($types);
		
		$intersection = array_shift($types);
		while (count($types) > 0) {
			$intersection = static::intersectTwo($intersection, array_shift($types), $scope);
			if (!$intersection) return null;
		}
		
		return $intersection;
	}
	
	/// Intersects two types and returns whatever they have in common, or null if they are entirely different.
	static public function intersectTwo(Type $a, Type $b, $scope = null)
	{
		if ($a === $b) return $a;
		if ($a instanceof GenericType) return $b;
		if ($b instanceof GenericType) return $a;
		//echo "intersectTwo {$a->details()} and {$b->details()}\n";
		
		//Choose the more specific scope to be used for the intersection.
		if (!$scope) {
			$scope = $a->scope;
			$s = $b->scope;
			while ($s) {
				if ($s == $scope) {
					$scope = $b->scope;
					break;
				}
				$s = $s->outer;
			}
		}
		
		if (!$a instanceof TypeSet && $b instanceof TypeSet) return static::intersectTwo($b, $a, $scope);
		if ($a instanceof TypeSet) {
			$types = array();
			foreach ($a->types as $type) {
				$t = static::intersectTwo($type, $b, $scope);
				if ($t) $types[] = $t;
			}
			if (!count($types)) return null;
			if (count($types) == 1) return array_shift($types);
			return new TypeSet($scope, $types);
		}
		
		if (!$a instanceof TypeTuple && $b instanceof TypeTuple) return static::intersectTwo($b, $a, $scope);
		if ($a instanceof TypeTuple && !$b instanceof TypeTuple) {
			$fields = $a->fields;
			if (count($fields) == 1) return static::intersectTwo(array_shift($fields), $b, $scope);
			return null;
		}
		if ($a instanceof TypeTuple && $b instanceof TypeTuple) {
			if (count($a->fields) != count($b->fields)) return null;
			$fields = array();
			$pairs = TypeTuple::fieldPairs($a, $b);
			foreach ($pairs as $ak => $bk) {
				$af = $a->fields[$ak];
				$bf = $b->fields[$bk];
				$type = static::intersectTwo($af, $bf, $scope);
				if (!$type) return null;
				if (is_string($ak)) $fields[$ak] = $type; else
				if (is_string($bk)) $fields[$bk] = $type;
				else $fields[] = $type;
			}
			return new TypeTuple($scope, $fields);
		}
		
		if (!$a instanceof MemberConstrainedType && $b instanceof MemberConstrainedType) return static::intersectTwo($b, $a, $scope);
		if ($a instanceof MemberConstrainedType && !$b instanceof MemberConstrainedType) {
			$type = static::intersectTwo($a->type, $b, $scope);
			if (!$type || !$type instanceof ConcreteType) return null;
			
			//Strip members whose type constraint is met.
			$members = $a->members;
			foreach ($b->members() as $member) {
				$name = $member->name();
				if (!isset($members[$name])) continue;
				$inter = static::intersectTwo($members[$name], $member->type(), $scope);
				if (!$inter) return null;
				if ($inter === $member->type()) unset($members[$name]);
			}
			
			if (!$members) return $b;
			return new MemberConstrainedType($type, $members, $a->issuingNodes);
		}
		if ($a instanceof MemberConstrainedType && $b instanceof MemberConstrainedType) {
			$type = static::intersectTwo($a->type, $b->type, $scope);
			if (!$type) return null;
			$members = array();
			foreach ($a->members as $m => $t) {
				if (isset($b->members[$m])) $t = static::intersectTwo($t, $b->members[$m], $scope);
				if (!$t) return null;
				$members[$m] = $t;
			}
			foreach ($b->members as $m => $t) {
				if (!isset($a->members[$m])) $members[$m] = $t;
			}
			return new MemberConstrainedType($type, $members, array_merge($a->issuingNodes, $b->issuingNodes));
		}
		
		if ($a instanceof FuncType && $b instanceof FuncType) {
			\mwc\debug("    - intersect FuncType {$a->details()} and {$b->details()}\n");
			$in  = static::intersectTwo($a->in(),  $b->in(),  $scope);
			$out = static::intersectTwo($a->out(), $b->out(), $scope);
			if (!$in || !$out) return null;
			return new FuncType($scope, $in, $out);
		}
		
		if (!$a instanceof ConcreteType_Spec && $b instanceof ConcreteType_Spec) return static::intersectTwo($b, $a, $scope);
		if ($a instanceof ConcreteType_Spec && $b instanceof ConcreteType) {
			if ($a->name() != $b->name()) return null;
			return $a;
		}
		if ($a instanceof ConcreteType && $b instanceof ConcreteType) {
			//\mwc\debug("      - intersect types {$a->desc()} {$a->tag} and {$b->desc()} {$b->tag}\n");
			return ($a === $b ? $a : null);
		}
		return null;
	}
	
	public function isSpecific() { return false; }
}