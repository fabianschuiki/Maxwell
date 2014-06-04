<?php
namespace C;

class Node
{
	static public function indent($str)
	{
		return "\t".str_replace("\n", "\n\t", trim($str));
	}
	
	public function __construct() {}
}