<?php
/* Copyright © 2013 Fabian Schuiki */

interface AbstractFunction
{
	public function setInputs(AbstractFunctionArgumentTuple $inputs = null, $notify = true);
	public function getInputs($enforce = true);
	
	public function setOutputs(AbstractFunctionArgumentTuple $outputs = null, $notify = true);
	public function getOutputs($enforce = true);
}