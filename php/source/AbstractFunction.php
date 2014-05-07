<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunction extends NamedObject, TypedObject
{
	public function getInputs();
	public function getOutputs();
}