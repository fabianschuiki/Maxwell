<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface RangeInterface
{
	public function setRange(\Source\Range $range = null, $notify = true);
	public function getRange($enforce = true);
	
	public function setHumanRange(\Source\Range $humanRange = null, $notify = true);
	public function getHumanRange($enforce = true);
}