<?php

class CSegment
{
	public $comment = null;
	public $stmts = array();
	public $expr = null;
	public $exprIsRef = false;
	public $hstmts = array();
	
	public function addStmts(array $s)
	{
		foreach ($s as $t) {
			$this->stmts[] = $t;
		}
	}
	
	public function addHStmts(array $s)
	{
		foreach ($s as $t) {
			$this->hstmts[] = $t;
		}
	}
	
	public function add($s)
	{
		if ($s instanceof CSegment) {
			$this->addStmts ($s->stmts);
			$this->addHStmts($s->hstmts);
		}
	}
}