<?php
/* Copyright © 2013 Fabian Schuiki */

interface RepositoryObjectParentInterface
{
	public function setParent(RepositoryObject $parent, $key = null, $fragment = null);
}