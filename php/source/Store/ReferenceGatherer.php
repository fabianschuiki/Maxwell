<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Store;

class ReferenceGatherer
{
	/**
	 * Recursively iterates through the given entity and compiles a list of
	 * entities the entity references.
	 */
	static public function gatherReferencedEntities(\Entity\Entity $entity)
	{
		$entities = array();
		static::_gatherReferencedEntities($entity, $entities);
		return array_filter($entities, function($e) use ($entity) {
			return strpos($e->getID(), $entity->getID()) !== 0;
		});
	}

	static private function _gatherReferencedEntities(\Entity\Entity $entity, array &$pool)
	{
		//if (!$entity instanceof \Entity\Expr\Type) {
			foreach ($entity->getChildEntities() as $e) {
				static::_gatherReferencedEntities($e, $pool);
			}
		//}

		// Keep track of bound entities.
		if (isset($entity->analysis->binding)) {
			$target = $entity->analysis->binding->target;
			if ($target instanceof \Entity\Entity && !in_array($target, $pool, true)) {
				$pool[] = $target;
			}
		}

		// Keep track of types.
		if (isset($entity->analysis->type)) {
			foreach (array("initial", "inferred") as $property) {
				$type = $entity->analysis->type->$property;
				if ($type instanceof \Type\Defined) {
					$target = $type->getDefinition();
					if ($target && !in_array($target, $pool, true)) {
						$pool[] = $target;
					}
				}
			}
		}
	}
}