<?php
namespace Driver\Analyzer;
use IssueList;
use Entity\TypeDefinition;
use Source\Range;

class TypeSpecializer
{
	/**
	 * Duplicates the given type definition and specializes it with the given
	 * arguments. Range should point to the part of the source file that caused
	 * the specialization, e.g. the TypeSpec entity or similar.
	 *
	 * @return Returns the specialized TypeDefinition, or null if an error
	 * occurred. The current IssueList is populated with error descriptions.
	 */
	static public function specialize(TypeDefinition $type, array $args, Range $range)
	{
		IssueList::add('error', "Specialization of type {$type->getName()} is not yet implemented.", $range);
		return null;
	}
}