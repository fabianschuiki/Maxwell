<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunctionArgument extends NamedObject, TypedObject
{
	public function getType($enforce = true);
	public function getName($enforce = true);
}