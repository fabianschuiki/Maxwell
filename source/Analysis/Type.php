<?php
namespace Analysis;

/** Container class for type analysis information inferred by the analyzer. */
class Type
{
	/** The initial type as derived from the entities, with no type inferrence applied. */
	public $initial;
	
	/** The calculated type, based on the initial type and imposed constraints. */
	public $inferred;

	public function copyFrom(self $f)
	{
		$this->initial  = ($f->initial ? $f->initial->copy() : null);
		$this->inferred = ($f->inferred ? $f->inferred->copy() : null);
	}
}