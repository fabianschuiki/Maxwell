<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface TypeInterface
{
	public function setPossibleType($possibleType, $notify = true);
	public function setPossibleTypeRef($possibleType, \Repository $repository, $notify = true);
	public function getPossibleType($enforce = true, $unref = true);
	
	public function setRequiredType($requiredType, $notify = true);
	public function setRequiredTypeRef($requiredType, \Repository $repository, $notify = true);
	public function getRequiredType($enforce = true, $unref = true);
	
	public function setActualType($actualType, $notify = true);
	public function setActualTypeRef($actualType, \Repository $repository, $notify = true);
	public function getActualType($enforce = true, $unref = true);
}