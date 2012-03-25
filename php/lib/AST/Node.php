<?php
namespace AST;

class Node
{
	///Returns the type of this AST node, which is its class name without the AST namespace.
	public function type()
	{
		return preg_replace('/^'.preg_quote(__NAMESPACE__.'\\').'/', '', get_class($this));
	}
	
	public function range()
	{
		$range = null;
		foreach ($this as $key => $value) {
			if (is_object($value) && method_exists($value, 'range')) {
				$r = $value->range();
				if (!$range) {
					$range = $r;
				} else {
					$range->combine($r);
				}
			}
		}
		return $range;
	}
}
