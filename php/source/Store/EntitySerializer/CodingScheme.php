<?php
namespace Store\EntitySerializer;

/** Stores information on how to encode/decode a certain entity. */
class CodingScheme
{
	public $className;
	public $tagName;
	public $fields;
	
	public function __construct($className, $tagName, array $fields = array())
	{
		$this->className = $className;
		$this->tagName   = $tagName;
		$this->fields    = array();
		foreach ($fields as $field) {
			$type = $field[0];
			$name = substr($field, 1);
			$comps = explode(":", $name, 2);
			if (count($comps) == 2) {
				$name = $comps[0];
				$tag  = $comps[1];
			} else {
				$tag  = $name;
			}
			$f = new \stdClass;
			$f->type = $type;
			$f->name = $name;
			$f->tag  = $tag;
			$this->fields[] = $f;
		}
	}
}