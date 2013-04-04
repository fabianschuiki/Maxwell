<?php
/* Copyright © 2013 Fabian Schuiki */

interface RepositoryObjectParentInterface
{
	public function setParent(IdedObject $parent = null, $key = null, $fragment = null);
}