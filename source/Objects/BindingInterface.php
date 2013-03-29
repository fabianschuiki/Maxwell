<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface BindingInterface
{
	public function setBindingTarget(Expr $bindingTarget = null);
	public function getBindingTarget();
	
	public function setHumanRange(\Source\Range $humanRange = null);
	public function getHumanRange();
}