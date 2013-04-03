<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface TypeInterface
{
	public function setPossibleType(Type $possibleType = null, $notify = true);
	public function getPossibleType($enforce = true);
}