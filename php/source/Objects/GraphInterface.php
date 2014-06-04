<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated interface. */
namespace Objects;

interface GraphInterface
{
	public function setGraphPrev($graphPrev, $notify = true);
	public function setGraphPrevRef($graphPrev, \Repository $repository, $notify = true);
	public function getGraphPrev($enforce = true, $unref = true);
}