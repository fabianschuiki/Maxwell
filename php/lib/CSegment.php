<?php

class CSegment
{
	public $comment = null;
	public $stmts = array();
	public $expr = null;
	public $exprIsRef = false;
	
	public function addStmts($s)
	{
		if (is_array($s)) {
			foreach ($s as $t) {
				$this->stmts[] = $t;
			}
		}
	}
}