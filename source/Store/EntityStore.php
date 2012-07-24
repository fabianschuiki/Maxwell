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
		$root = new Coder\Element("root");
		$this->serializeRootEntity($entity, $root);
		
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
	
	private function serializeRootEntity(\Entity\RootEntity $entity, Coder\Element $root)
	{
		foreach ($entity->getSiblingEntities() as $sibling) {
			$e = $root->makeElement('sibling');
			$e->setAttribute('id', $sibling->getID());
		}
		
		if ($entity instanceof \Entity\FunctionDefinition) {
			$e = $root->makeElement('function');
			$e->setAttribute('id', $entity->getID());
			$e->setAttribute('range', $entity->getRange()->toString());
			$e->setAttribute('humanRange', $entity->getHumanRange()->toString());
			$e->setAttribute('file', $entity->getRange()->getFile()->getPath());
			$e->setAttribute('name', $entity->getName());
		}
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