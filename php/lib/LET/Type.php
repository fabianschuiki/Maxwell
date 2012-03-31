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
	
	/// Finds the largest common type (set, tuple, etc.) among a number of types.
	static public function intersect($types)
	{
		if (!is_array($types)) $types = func_get_args();
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
			$intersection = static::intersectTwo($intersection, array_shift($types));
			if (!$intersection) return null;
		}
		
		return $intersection;
	}
	
	/// Intersects two types and returns whatever they have in common, or null if they are entirely different.
	static private function intersectTwo(Type $a, Type $b)
	{
		if ($a instanceof GenericType) return $b;
		if ($b instanceof GenericType) return $a;
		
		//echo "intersectTwo {$a->details()} and {$b->details()}\n";
		
		if (!$a instanceof TypeSet && $b instanceof TypeSet) return static::intersectTwo($b, $a);
		if ($a instanceof TypeSet) {
			$types = array();
			foreach ($a->types as $type) {
				$t = static::intersectTwo($type, $b);
				if ($t) $types[] = $t;
			}
			if (!count($types)) return null;
			if (count($types) == 1) return array_shift($types);
			return new TypeSet($a->scope, $types);
		}
		
		if (!$a instanceof TypeTuple && $b instanceof TypeTuple) return static::intersectTwo($b, $a);
		if ($a instanceof TypeTuple && !$b instanceof TypeTuple) {
			$fields = $a->fields;
			if (count($fields) == 1) return static::intersectTwo(array_shift($fields), $b);
			return null;
		}
		if ($a instanceof TypeTuple && $b instanceof TypeTuple) {
			if (count($a->fields) != count($b->fields)) return null;
			$fields = array();
			$pairs = TypeTuple::fieldPairs($a, $b);
			foreach ($pairs as $ak => $bk) {
				$af = $a->fields[$ak];
				$bf = $b->fields[$bk];
				$type = static::intersectTwo($af, $bf);
				if (!$type) return null;
				if (is_string($ak)) $fields[$ak] = $type; else
				if (is_string($bk)) $fields[$bk] = $type;
				else $fields[] = $type;
			}
			return new TypeTuple($a->scope, $fields);
		}
		
		if (!$a instanceof MemberConstrainedType && $b instanceof MemberConstrainedType) return static::intersectTwo($b, $a);
		if ($a instanceof MemberConstrainedType && !$b instanceof MemberConstrainedType) {
			$type = static::intersectTwo($a->type, $b);
			if (!$type) return null;
			return new MemberConstrainedType($type, $a->members, $a->issuingNodes);
		}
		if ($a instanceof MemberConstrainedType && $b instanceof MemberConstrainedType) {
			$type = static::intersectTwo($a->type, $b->type);
			if (!$type) return null;
			$members = array();
			foreach ($a->members as $m => $t) {
				if (isset($b->members[$m])) $t = static::intersectTwo($t, $b->members[$m]);
				if (!$t) return null;
				$members[$m] = $t;
			}
			foreach ($b->members as $m => $t) {
				if (!isset($a->members[$m])) $members[$m] = $t;
			}
			return new MemberConstrainedType($type, $members, array_merge($a->issuingNodes, $b->issuingNodes));
		}
		
		if ($a instanceof FuncType && $b instanceof FuncType) {
			$in  = static::intersectTwo($a->in(),  $b->in());
			$out = static::intersectTwo($a->out(), $b->out());
			if (!$in || !$out) return null;
			return new FuncType($a->scope, $in, $out);
		}
		
		if (!$a instanceof ConcreteType_Spec && $b instanceof ConcreteType_Spec) return static::intersectTwo($b, $a);
		if ($a instanceof ConcreteType_Spec && $b instanceof ConcreteType) {
			if ($a->name() != $b->name()) return null;
			return $a;
		}
		if ($a instanceof ConcreteType && $b instanceof ConcreteType) return ($a === $b ? $a : null);
		return null;
	}
	
	public function isSpecific() { return false; }
}