<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface AssumerInterface
{
	public function setAssumptions($assumptions, $notify = true);
	public function setAssumptionsRef($assumptions, \Repository $repository, $notify = true);
	public function getAssumptions($enforce = true, $unref = true);
}