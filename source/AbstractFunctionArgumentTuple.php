<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunctionArgumentTuple extends TypedObject
{
	public function getArguments($enforce = true);
}