<?php
namespace C;

class Block extends Container
{
	public function getCode()
	{
		$str = "";
		foreach ($this->nodes as $node) {
			$str .= $node->getStmt()."\n";
		}
		return $str;
	}
}