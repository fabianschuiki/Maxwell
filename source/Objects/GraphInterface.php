<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface GraphInterface
{
	public function setGraphPrev(\RepositoryObjectReference $graphPrev = null, $notify = true);
	public function getGraphPrev($enforce = true);
}