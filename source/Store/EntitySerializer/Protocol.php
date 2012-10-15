<?php
namespace Store\EntitySerializer;

/** Stores generic information on how to serialize entities. */
class Protocol
{
	protected $schemes;
	
	public function __construct()
	{
		$this->schemes = array();
		
		$this->register("FunctionDefinition", "function");
		$this->register("TypeDefinition", "type");
	}
	
	public function getMainScheme(\Entity\Node $node)
	{
		foreach ($this->schemes as $s) {
			if ("\\".get_class($node) == $s->className)
				return $s;
		}
		return null;
	}
	
	public function getSchemes(\Entity\Node $node)
	{
		$schemes = array();
		foreach ($this->schemes as $s) {
			if ($node instanceof $s->className)
				$schemes[] = $s;
		}
		return $schemes;
	}
	
	protected function register($className, $tagName)
	{
		$s = new CodingScheme("\\Entity\\$className", $tagName);
		$this->schemes[] = $s;
		return $s;
	}
}