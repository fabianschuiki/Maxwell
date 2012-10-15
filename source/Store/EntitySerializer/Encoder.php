<?php
namespace Store\EntitySerializer;
use Coder;

class Encoder
{
	protected $protocol;
	
	protected $root;
	protected $entities;
	protected $analysis;
	
	public function __construct(Protocol $protocol)
	{
		$this->protocol = $protocol;
	}
	
	public function encode(\Entity\RootEntity $rootEntity)
	{
		$this->root = new Coder\Element("root");
		$this->root->setAttribute("id", $rootEntity->getID());
		$this->root->setAttribute("file", $rootEntity->getRange()->getFile()->getPath());
		
		//Encode the root entity.
		$this->encodeEntity($rootEntity);
		
		//Keep track of the known entities as well as the entity's siblings.
		foreach ($rootEntity->getSiblingEntities() as $sibling) {
			$e = $this->root->makeElement('sibling');
			$e->setAttribute('id', $sibling->getID());
		}
		foreach ($rootEntity->getKnownEntities() as $known) {
			$e = $this->root->makeElement('known');
			$e->setAttribute('id', $known->getID());
		}
		
		return $this->root;
	}
	
	protected function getEntities()
	{
		if (!$this->entities) $this->entities = $this->root->makeElement("entities");
		return $this->entities;
	}
	
	protected function getAnalysis()
	{
		if (!$this->analysis) $this->analysis = $this->root->makeElement("analysis");
		return $this->analysis;
	}
	
	protected function encodeEntity(\Entity\Node $entity)
	{
		//Find the schemes that apply to this entity.
		$mainScheme = $this->protocol->getMainScheme($entity);
		$schemes    = $this->protocol->getSchemes($entity);
		if (!$mainScheme) {
			throw new \exception("No scheme available to encode ".vartype($entity));
		}
		
		//Create the element for this entity.
		$element = $this->getEntities()->makeElement($mainScheme->tagName);
		$element->setAttribute("id", $entity->getID());
		
		//If applicable, encode the ranges for this entity.
		if ($entity instanceof \Entity\Entity) {
			$element->setAttribute('range', $entity->getRange()->toString());
			if ($entity->getHumanRange()) {
				$element->setAttribute('humanRange', $entity->getHumanRange()->toString());
			}
		}
		
		//Perform specific encoding for this entity if applicable.
		$specificName = "encode".str_replace("\\", "", get_class($entity));
		if (method_exists($this, $specificName)) {
			$this->$specificName($entity, $element);
		}
	}
	
	protected function encodeEntityFunctionDefinition(\Entity\FunctionDefinition $entity, Coder\Element $element)
	{
		$element->setAttribute("rulez", "verymuchsir");
	}
}