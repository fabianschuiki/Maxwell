<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunctionArgument extends NamedObject
{
	public function setTypeExpr(TypeExpr $typeExpr = null, $notify = true);
	public function getTypeExpr($enforce = true);
	
	public function setName($name, $notify = true);
	public function getName($enforce = true);
}