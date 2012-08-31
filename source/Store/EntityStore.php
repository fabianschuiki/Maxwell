<?php
namespace Store;
use Source\File;
use Coder;

class EntityStore
{
	protected $manager;
	protected $dir;
	protected $entities;
	
	public function __construct(Manager $manager)
	{
		$this->manager = $manager;
		$this->dir = $manager->getDirectory()."/entities";
		$this->entities = array();
	}
	
	public function allocateId()
	{
		return $this->manager->allocateId();
	}
	
	public function clearEntitiesInFile(\Source\File $file)
	{
		
	}
	
	public function setEntity(\Entity\RootEntity $entity)
	{
		$id = $entity->getID();
		if ($id <= 0) throw new \exception("setting entity ".vartype($entity)." with no ID");
		
		$this->entities[$id] = $entity;
		
		//Transform the tokens into an encodable representation.
		$root = static::serializeRootEntity($entity);
		
		//Persist the tokens.
		$path = $this->getPathToEntity($id);
		$dir = dirname($path);
		if (!file_exists($dir)) @mkdir($dir, 0777, true);
		
		$xml = new Coder\XMLCoder;
		$xml->encodeToFile($root, $path);
	}
	
	public function getEntity($id)
	{
		$e = @$this->entities[$id];
		if (!$e) trigger_error("Entity decoding not implemented yet", E_USER_ERROR);
		return $e;
	}
	
	
	private function getPathToEntity($id)
	{
		return "{$this->dir}/$id";
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
	
	/*private function serializeTokens(TokenList $tokens, Coder\Element $parent)
	{
		foreach ($tokens->getTokens() as $t) {
			$e = $parent->makeElement($t->getType());
			$e->setAttribute('id', $t->getID());
			$e->setAttribute('text', $t->getText());
			$e->setAttribute('range', $t->getRange()->toString());
			if ($t->is('group'))
				$this->serializeTokens($t->getTokens(), $e);
		}
	}*/
}