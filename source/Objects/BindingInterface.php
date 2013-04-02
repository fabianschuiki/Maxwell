<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface BindingInterface
{
	public function setBindingTarget(\RepositoryObjectReference $bindingTarget = null, $notify = true);
	public function getBindingTarget($enforce = true);
}