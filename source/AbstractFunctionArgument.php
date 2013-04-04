<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunctionArgument extends NamedObject, TypedObject
{
	public function getTypeExpr($enforce = true);
	public function getName($enforce = true);
}