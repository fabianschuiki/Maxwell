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
	
	static public function fieldPairs(TypeTuple $a, TypeTuple $b)
	{
		$pairs = array();
		
		$nameFilter  = function($v) { return is_string($v); };
		$an = array_filter(array_keys($a->fields), $nameFilter);
		$bn = array_filter(array_keys($b->fields), $nameFilter);
		$names = array_intersect($an, $bn);
		foreach ($names as $name) $pairs[] = array($name, $name);
		
		$af = array_values(array_diff(array_keys($a->fields), $names));
		$bf = array_values(array_diff(array_keys($b->fields), $names));
		
		$indexFilter = function($v) { return is_int($v); };
		
		$ai = array_keys(array_filter($af, $indexFilter));
		while (count($ai) > 0) {
			$afkey = array_shift($ai);
			if (count($bf) > 0) {
				$ak = $af[$afkey];
				$bk = array_shift($bf);
				$pairs[] = array($ak, $bk);
				unset($af[$afkey]);
			}
		}
		
		$bi = array_keys(array_filter($bf, $indexFilter));
		while (count($bi) > 0) {
			$bfkey = array_shift($bi);
			if (count($af) > 0) {
				$ak = array_shift($af);
				$bk = $bf[$bfkey];
				$pairs[] = array($ak, $bk);
				unset($bf[$bfkey]);
			}
		}
		
		$missing = array_merge($af, $bf);
		if (count($missing)) {
			$fields = implode(', ', $missing);
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Type tuple '{$a->details()}' and '{$b->details()}' don't share the fields $fields."
			);
		}
		
		return $pairs;
	}
}