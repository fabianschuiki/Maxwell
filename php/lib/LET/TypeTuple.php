<?php
namespace LET;

class TypeTuple extends Type
{
	public $fields;
	
	public function __construct(Scope $scope, array $fields)
	{
		$this->fields = $fields;
		$this->scope  = $scope;
	}
	
	public function details()
	{
		$fields = array();
		foreach ($this->fields as $name => $field) {
			if (!$field) throw new \RuntimeException("TypeTuple field $name has null type.");
			$str = $field->details();
			if (is_string($name)) $str = "$name: $str";
			$fields[] = $str;
		}
		$fields = implode(', ', $fields);
		
		return "($fields)";
	}
	
	public function children() { return array_values($this->fields); }
	
	public function isSpecific()
	{
		foreach ($this->fields as $name => $field) {
			if (!$field->isSpecific()) return false;
		}
		return true;
	}
	
	static public function fieldPairs($a, $b)
	{
		$pairs = array();
		assert($a instanceof TypeTuple || is_array($a));
		assert($b instanceof TypeTuple || is_array($b));
		
		$an0 = ($a instanceof TypeTuple ? array_keys($a->fields) : $a);
		$bn0 = ($b instanceof TypeTuple ? array_keys($b->fields) : $b);
		
		$nameFilter  = function($v) { return is_string($v); };
		$an = array_filter($an0, $nameFilter);
		$bn = array_filter($bn0, $nameFilter);
		$names = array_intersect($an, $bn);
		foreach ($names as $name) $pairs[$name] = $name;
		
		$af = array_values(array_diff($an0, $names));
		$bf = array_values(array_diff($bn0, $names));
		
		$indexFilter = function($v) { return is_int($v); };
		
		$ai = array_keys(array_filter($af, $indexFilter));
		while (count($ai) > 0) {
			$afkey = array_shift($ai);
			if (count($bf) > 0) {
				$ak = $af[$afkey];
				$bk = array_shift($bf);
				$pairs[$ak] = $bk;
				unset($af[$afkey]);
			}
		}
		
		$bi = array_keys(array_filter($bf, $indexFilter));
		while (count($bi) > 0) {
			$bfkey = array_shift($bi);
			if (count($af) > 0) {
				$ak = array_shift($af);
				$bk = $bf[$bfkey];
				$pairs[$ak] = $bk;
				unset($bf[$bfkey]);
			}
		}
		
		/*$missing = array_merge($af, $bf);
		if (count($missing)) {
			$fields = implode(', ', $missing);
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Type tuple '{$a->details()}' and '{$b->details()}' don't share the fields $fields."
			);
		}*/
		
		return $pairs;
	}
	
	
	public function reduceToAbsolute(Scope $scope)
	{
		return new TypeTuple($scope, array_map(function($f) use ($scope) { return $f->reduceToAbsolute($scope); }, $this->fields));
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		foreach ($this->fields as $name => &$field) $field = $field->unbindFromInterfaces($root);
		return parent::unbindFromInterfaces($root);
	}
}