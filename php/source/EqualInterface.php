<?php
/* Copyright © 2013 Fabian Schuiki */

interface EqualInterface
{
	/**
	 * @brief Returns true if this object is equal to x.
	 * This function assumes that x is of the same class as the object!
	 */
	public function isEqualTo($x);
}