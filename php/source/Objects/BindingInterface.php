<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface BindingInterface
{
	public function setBindingTarget($bindingTarget, $notify = true);
	public function setBindingTargetRef($bindingTarget, \Repository $repository, $notify = true);
	public function getBindingTarget($enforce = true, $unref = true);
}