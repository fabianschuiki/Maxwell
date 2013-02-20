<?php
namespace Driver\Analyzer;
use IssueList;
use Entity\TypeDefinition;
use Source\Range;
use Store\Manager;

class TypeSpecializer
{
	/**
	 * Duplicates the given type definition and specializes it with the given
	 * arguments. Range should point to the part of the source file that caused
	 * the specialization, e.g. the TypeSpec entity or similar.
	 *
	 * @return Returns the specialized TypeDefinition, or null if an error
	 * occurred. The returned type may be the same as the one passed as an
	 * argument. The current IssueList is populated with error descriptions.
	 */
	static public function specialize(TypeDefinition $type, array $args, Range $range)
	{
		//Ignore specializations without any arguments.
		if (!count($args)) {
			return $type;
		}

		//Check whether the specialization already exists.
		// ... do this later ...

		//Duplicate the type, generate an appropriate ID and add it to the entity store.
		$entityStore = Manager::get()->getEntityStore();
		$entityStore->pushRootID($type->getID());
		$cloned = $type->copy();
		echo "cloned {$type->getName()} has ID {$cloned->getID()}\n";
		$entityStore->popRootID($type->getID());
		$entityStore->setEntity($cloned);
		$type->addKnownEntity($cloned);

		//Specialize the cloned entity's type variables.
		$args_left = $args;
		foreach ($cloned->getTypeVars() as $tv) {
			if (!count($args_left)) break;
			$arg = array_shift($args_left);
			$type = $arg->getType();
			if (!$type) {
				IssueList::add('error', "Specialization argument has no valid type.", $arg);
				return null;
			}
			$tv->setType($type);
			echo "Setting {$tv->getName()}'s type to {$type->toHumanReadableString()}\n";
		}

		return $cloned;
	}
}