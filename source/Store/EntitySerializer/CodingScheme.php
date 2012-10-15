<?php
namespace Store\EntitySerializer;

/** Stores information on how to encode/decode a certain entity. */
class CodingScheme
{
	public $className;
	public $tagName;
	
	public function __construct($className, $tagName)
	{
		$this->className = $className;
		$this->tagName   = $tagName;
	}
}