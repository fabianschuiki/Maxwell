<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface RangeInterface
{
	public function setRange($range, $notify = true);
	public function setRangeRef($range, \Repository $repository, $notify = true);
	public function getRange($enforce = true, $unref = true);
	
	public function setHumanRange($humanRange, $notify = true);
	public function setHumanRangeRef($humanRange, \Repository $repository, $notify = true);
	public function getHumanRange($enforce = true, $unref = true);
}