<?php
namespace Store;
use Source\File;
use Coder;

class EntityStore
{
	protected $manager;
	protected $dir;
	protected $entities;
	protected $entityIDsInFile;
	
	public function __construct(Manager $manager)
	{
		$this->manager = $manager;
		$this->dir = $manager->getDirectory()."/entities";
		$this->entities = array();
		$this->entityIDsInFile = array();
	}
	
	public function allocateId()
	{
		return $this->manager->allocateId();
	}
	
	public function clearEntitiesInFile(\Source\File $file)
	{
		//Load the IDs that are in this file.
		$ids = $this->getEntityIDsInFile($file->getPath());
		if (!$ids) return;
		
		//Get rid of the entities.
		foreach ($ids as $id)
			$this->unpersistEntity($id);
		unset($this->entityIDsInFile[$file->getPath()]);
	}
	
	public function setEntity(\Entity\RootEntity $entity)
	{
		$id = $entity->getID();
		if ($id <= 0) throw new \exception("setting entity ".vartype($entity)." with no ID");
		$path = $entity->getRange()->getFile()->getPath();
		
		$this->entities[$id] = $entity;
		$this->entityIDsInFile[$path][] = $id;
		
		$this->persistEntity($id);
		$this->persistEntityIDsInFile($path);
	}
	
	public function getEntity($id)
	{
		$e = @$this->entities[$id];
		if (!$e) trigger_error("Entity decoding not implemented yet", E_USER_ERROR);
		return $e;
	}
	
	public function getEntityIDsInFile($path)
	{
		$ids = @$this->entityIDsInFile[$path];
		if (!$ids) {
			$this->fetchEntityIDsInFile($path);
			$ids = @$this->entityIDsInFile[$path];
		}
		return $ids;
	}
	
	
	/*
	 * Entities
	 */
	
	private function persistEntity($id)
	{
		$entity = $this->entities[$id];
		
		//Transform the tokens into an encodable representation.
		$root = static::serializeRootEntity($entity);
		
		//Persist the entity.
		$path = $this->getPathToEntity($id);
		static::ensureDirExists($path);
		
		$xml = new Coder\XMLCoder;
		$xml->encodeToFile($root, $path);
	}
	
	private function unpersistEntity($id)
	{
		$entity = @$this->entities[$id];
		
		//Remove the entity from our structures.
		if ($entity) unset($this->entities[$id]);
		
		//Get rid of the entity file.
		$path = $this->getPathToEntity($id);
		if (file_exists($path)) unlink($path);
	}
	
	static private function serializeRootEntity(\Entity\RootEntity $entity)
	{
		if ($entity instanceof \Entity\FunctionDefinition) {
			$root = new Coder\Element("function");
			$root->setAttribute('id', $entity->getID());
			$root->setAttribute('range', $entity->getRange()->toString());
			$root->setAttribute('humanRange', $entity->getHumanRange()->toString());
			$root->setAttribute('file', $entity->getRange()->getFile()->getPath());
			$root->setAttribute('name', $entity->getName());
		}
		
		if ($root) {
			foreach ($entity->getSiblingEntities() as $sibling) {
				$e = $root->makeElement('sibling');
				$e->setAttribute('id', $sibling->getID());
			}
		}
		
		return $root;
	}
	
	
	/*
	 * Identity IDs in File
	 */
	
	private function persistEntityIDsInFile($file)
	{
		$ids = array_unique($this->entityIDsInFile[$file]);
		
		//Serialize the IDs.
		sort($ids);
		$text = implode("\n", $ids);
		
		//Store the entity IDs.
		$path = $this->getPathToEntityIDsInFile($file);
		static::ensureDirExists($path);
		file_put_contents($path, $text);
	}
	
	private function fetchEntityIDsInFile($file)
	{
		//Read the list of entities.
		$path = $this->getPathToEntityIDsInFile($file);
		if (!file_exists($path)) return;
		$text = file_get_contents($path);
		
		//Decode the IDs and store them.
		$ids = explode("\n", trim($text));
		$this->entityIDsInFile[$file] = $ids;
	}
	
	
	/*
	 * Paths
	 */
	
	private function getPathToEntity($id)
	{
		return "{$this->dir}/$id";
	}
	
	private function getPathToEntityIDsInFile($path)
	{
		$name = preg_replace('/\.mw$/i', '.entities', $path);
		return "{$this->dir}/$name";
	}
	
	static private function ensureDirExists($path)
	{
		$dir = dirname($path);
		if (!file_exists($dir)) @mkdir($dir, 0777, true);
	}
}