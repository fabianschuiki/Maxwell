<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunction extends NamedObject
{
	public function getInputs($enforce = true);
	public function getOutputs($enforce = true);
}