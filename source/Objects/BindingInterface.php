<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface BindingInterface
{
	public function setBindingTarget(Expr $bindingTarget = null, $notify = true);
	public function getBindingTarget($enforce = true);
	
	public function setBindingDebug($bindingDebug, $notify = true);
	public function getBindingDebug($enforce = true);
}