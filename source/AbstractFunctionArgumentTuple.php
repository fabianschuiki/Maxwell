<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunctionArgumentTuple
{
	public function setArguments(RepositoryObjectArray $arguments = null, $notify = true);
	public function getArguments($enforce = true);
}