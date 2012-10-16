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
			if ($sibling == $rootEntity) continue;
			$e = $this->root->makeElement('sibling');
			$e->setAttribute('id', $sibling->getID());
		}
		foreach ($rootEntity->getKnownEntities() as $known) {
			if ($known == $rootEntity) continue;
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
		
		//Perform the encoding according to the schemes.
		foreach ($schemes as $scheme) {
			foreach ($scheme->fields as $field) {
				$func  = "get".strtoupper($field->name);
				if (!method_exists($entity, $func)) {
					throw new \exception(vartype($entity)." does not support function $func as defined by {$scheme->tagName}.{$field->name}");
				}
				$value = $entity->$func();
				if ($value !== null) {
					if ($field->type == "&") {
						$element->setAttribute($field->tag, $value);
					} else {
						$element->setAttribute($field->tag, $value->getID());
						if ($field->type == "@") {
							$this->encodeEntity($value);
						}
					}
				}
			}
		}
		
		//Perform specific encoding for this entity if applicable.
		$specificName = "encode".str_replace("\\", "", get_class($entity));
		if (method_exists($this, $specificName)) {
			$this->$specificName($entity, $element);
		}
		
		//Encode the analysis if applicable.
		if (isset($entity->analysis)) {
			$this->encodeAnalysis($entity->analysis);
		}
		
		//Encode the compiler data if applicable.
		if (isset($entity->compiler)) {
			$this->encodeCompiler($entity->compiler);
		}
	}
	
	protected function encodeAnalysis(\Analysis\Node\Node $analysis)
	{
		$entity = $analysis->entity;
		if (!$entity) {
			throw new \exception("No entity associated with analysis ".vartype($analysis));
		}
		
		if (isset($analysis->binding)) {
			$element = $this->getAnalysis()->makeElement("binding");
			$element->setAttribute("id", $entity->getID());
			$this->encodeAnalysisBinding($analysis->binding, $element);
		}
		if (isset($analysis->type)) {
			$element = $this->getAnalysis()->makeElement("type");
			$element->setAttribute("id", $entity->getID());
			$this->encodeAnalysisType($analysis->type, $element);
		}
	}
	
	protected function encodeAnalysisBinding(\Analysis\Binding $binding, Coder\Element $element)
	{
		if ($t = $binding->target) {
			if ($t instanceof \Type\Type) {
				if (!$t instanceof \Type\Builtin) throw new \exception("Identifier can only bind to builtin types.");
				$element->setAttribute('target', "builtin:{$t->getName()}");
			} else {
				$element->setAttribute('target', $t->getID());
			}
		}
	}
	
	protected function encodeAnalysisType(\Analysis\Type $type, Coder\Element $element)
	{
		if ($i = $type->initial)  $this->encodeAnalysisTypeType($i, $element)->setAttribute('rel', 'initial');
		if ($i = $type->inferred) $this->encodeAnalysisTypeType($i, $element)->setAttribute('rel', 'inferred');
		if ($i = $type->required) $this->encodeAnalysisTypeType($i, $element)->setAttribute('rel', 'required');
	}
	
	protected function encodeAnalysisTypeType(\Type\Type $type, Coder\Element $element)
	{
		$e = null;
		if ($type instanceof \Type\Generic) {
			$e = $element->makeElement("type-generic");
		}
		if ($type instanceof \Type\Builtin) {
			$e = $element->makeElement("type-builtin");
			$e->setAttribute('name', $type->getName());
		}
		if ($type instanceof \Type\Defined) {
			$e = $element->makeElement("type-defined");
			$e->setAttribute('definition', $type->getDefinition()->getID());
		}
		
		if (!$e) throw new \exception("Unable to encode type ".vartype($type));
		return $e;
	}
	
	protected function encodeCompiler(\Compiler\Node\Node $compiler)
	{
	}
	
	protected function encodeEntityTypeDefinition(\Entity\TypeDefinition $entity, Coder\Element $element)
	{
		foreach ($entity->getMembers() as $member) {
			$this->encodeEntity($member);
			$e = $element->makeElement("member");
			$e->setAttribute("id", $member->getID());
		}
	}
	
	protected function encodeEntityBlock(\Entity\Block $entity, Coder\Element $element)
	{
		foreach ($entity->getStmts() as $stmt) {
			$this->encodeEntity($stmt);
			$e = $element->makeElement('stmt');
			$e->setAttribute('id', $stmt->getID());
		}
	}
	
	protected function encodeEntityFuncTuple(\Entity\Func\Tuple $entity, Coder\Element $element)
	{
		foreach ($entity->getArgs() as $arg) {
			$this->encodeEntity($arg);
			$e = $element->makeElement('arg');
			$e->setAttribute('id', $arg->getID());
		}
	}
}