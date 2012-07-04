<?php
namespace Coder;

class Element
{
	protected $name;
	protected $attributes;
	protected $elements;
	
	public function __construct($name)
	{
		assert(is_string($name));
		$this->name = $name;
		$this->attributes = array();
		$this->elements = array();
	}
	
	public function getName() { return $this->name;	}
	public function getAttributes() { return $this->attributes; }
	public function hasElements() { return count($this->elements) > 0; }
	
	public function setAttribute($name, $value)
	{
		$this->attributes[$name] = $value;
	}
	
	public function getAttribute($name)
	{
		if (isset($this->attributes[$name]))
			return $this->attributes[$name];
		return null;
	}
	
	public function makeElement($name)
	{
		$e = new Element($name);
		$this->elements[] = $e;
		return $e;
	}
	
	public function getElements($name = null)
	{
		if ($name)
			return array_filter($this->elements, function($e) use ($name) { return $e->getName() == $name; });
		return $this->elements;
	}
	
	public function addElement(Element $e)
	{
		$this->elements[] = $e;
	}
	
	public function removeElement(Element $e)
	{
		$this->elements = array_filter($this->elements, function($f) use ($e) { return $e !== $f; });
	}
}