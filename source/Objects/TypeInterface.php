<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface TypeInterface
{
	public function setPossibleType($possibleType, $notify = true);
	public function getPossibleType($enforce = true);
	
	public function setRequiredType($requiredType, $notify = true);
	public function getRequiredType($enforce = true);
}