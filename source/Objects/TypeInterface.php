<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface TypeInterface
{
	public function setType(Type $type = null);
	public function getType();
	
	public function setHumanRange(\Source\Range $humanRange = null);
	public function getHumanRange();
}