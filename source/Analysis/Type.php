<?php
namespace Analysis;

/** Container class for type analysis information inferred by the analyzer. */
class Type
{
	/** The initial type as derived from the entities, with no type inferrence applied. */
	public $initial;
	
	/** The calculated type, based on the initial type and imposed constraints. */
	public $inferred;
	
	/** The type requirement as imposed by outer entities. */
	public $required;
}