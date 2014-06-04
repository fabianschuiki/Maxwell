<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface ExprCodeInterface
{
	public function setExprCode($exprCode, $notify = true);
	public function getExprCode($enforce = true);
	
	public function setStmtsCode($stmtsCode, $notify = true);
	public function getStmtsCode($enforce = true);
}