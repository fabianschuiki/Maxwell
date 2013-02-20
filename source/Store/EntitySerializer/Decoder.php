<?php
namespace Store\EntitySerializer;
use Coder;

class Decoder
{
	protected $protocol;
	protected $entityStore;
	
	protected $root;
	protected $entitiesRoot;
	protected $analysisRoot;
	protected $file;
	
	protected $siblingIDs;
	protected $knownIDs;
	protected $subrootEntities;
	
	protected $rootEntity;
	protected $entityElements;
	protected $entities;
	
	public function getRootEntity() { return $this->rootEntity; }
	public function getEntityIDs() { return array_keys($this->entities); }
	
	public function __construct(Protocol $protocol, \Store\EntityStore $entityStore)
	{
		$this->protocol    = $protocol;
		$this->entityStore = $entityStore;
	}
	
	public function decodeScaffold(Coder\Element $root)
	{
		$this->root = $root;
		
		//Keep track of the original source file.
		if ($p = $root->getAttribute('file')) {
			$this->file = new \Source\File($p);
		} else {
			throw new \exception("Root element has no file set");
		}
		
		//Decode the top layer of the root element.
		$this->siblingIDs = array();
		$this->knownIDs   = array();
		foreach ($root->getElements() as $element) {
			switch ($element->getName()) {
				case "entities": $this->entitiesRoot = $element; break;
				case "analysis": $this->analysisRoot = $element; break;
				case "sibling": $this->siblingIDs[] = $element->getAttribute("id"); break;
				case "known":   $this->knownIDs[]   = $element->getAttribute("id"); break;
			}
		}
		
		//Create a new object for each of the entities.
		$this->entityElements = array();
		$this->entities = array();
		$this->subrootEntities = array();
		foreach ($this->entitiesRoot->getElements() as $element) {
			$className = $this->protocol->getClassForTagName($element->getName());
			if (!$className) {
				throw new \exception("No scheme exists to resolve '{$element->getName()}' to a class name");
			}
			
			$entity = new $className;
			if ($id = $element->getAttribute("id")) {
				$entity->setID($id);
			} else {
				throw new \exception("Entity {$element->getName()} has no id");
			}
			$this->entities[$id]       = $entity;
			$this->entityElements[$id] = $element;
			if ($entity instanceof \Entity\RootEntity) {
				$this->subrootEntities[$id] = $entity;
			}
		}
		
		//Resolve the root entity.
		if ($id = $root->getAttribute("id")) {
			$this->rootEntity = $this->findEntity($id);
			$this->rootEntity->setFile($this->file);
			unset($this->subrootEntities[$id]);
			$this->rootEntity->setEmbeddedRootEntities($this->subrootEntities);
		} else {
			throw new \exception("No root ID specified in root element");
		}
	}
	
	protected function findEntity($id)
	{
		if ($e = @$this->entities[$id]) {
			return $e;
		}
		else if (($dot = strpos($id, ".")) !== false) {
			$rootID = substr($id, 0, $dot);
			$root = $this->findEntity($rootID);

			$embeddedRoots = $root->getEmbeddedRootEntities();
			$er = @$embeddedRoots[$id];
			if ($er) return $er;

			foreach ($root->getKnownEntities() as $e) {
				if ($e->getID() == $id)
					return $e;
			}
		}
		foreach ($this->rootEntity->getKnownEntities() as $e) {
			if ($e->getID() == $id)
				return $e;
		}
		throw new \exception("Unable to find entity $id");
	}
	
	public function decode()
	{
		//Resolve the siblings and known entities.
		$siblings = array();
		$known    = array();
		foreach ($this->siblingIDs as $id) {
			$siblings[] = $this->entityStore->getEntity($id);
		}
		foreach ($this->knownIDs as $id) {
			$known[] = $this->entityStore->getEntity($id);
		}
		$this->rootEntity->setSiblingEntities($siblings);
		$this->rootEntity->setKnownEntities($known);
		
		//Decode each entity individually.
		foreach ($this->entityElements as $id => $element) {
			$entity = $this->findEntity($id);
			$this->decodeEntity($entity, $element);
		}
		
		//Decode the analysis elements.
		if ($this->analysisRoot) {
			foreach ($this->analysisRoot->getElements() as $element) {
				$id = $element->getAttribute("id");
				if (!$id) {
					throw new \exception("Analysis node {$element->getName()} has no ID");
				}
				
				$entity = $this->findEntity($id);
				$this->decodeAnalysis($entity->analysis, $element);
			}
		}
	}
	
	protected function decodeEntity(\Entity\Node $entity, Coder\Element $element)
	{
		//Find the decoding schemes that apply to this entity.
		$schemes = $this->protocol->getSchemes($entity);
		if (!count($schemes)) {
			throw new \exception("No schemes available to encode ".vartype($entity));
		}
		
		//If applicable, decode the ranges for this entity.
		if ($entity instanceof \Entity\Entity) {
			if ($r = $element->getAttribute("range")) {
				$entity->setRange(\Source\Range::fromString($r, $this->file));
			} else {
				throw new \exception("Entity ".vartype($entity)." has no range set");
			}
			if ($r = $element->getAttribute("humanRange")) {
				$entity->setHumanRange(\Source\Range::fromString($r, $this->file));
			}
		}
		
		//Perform the decoding according to the schemes.
		foreach ($schemes as $scheme) {
			foreach ($scheme->fields as $field) {
				$func  = "set".strtoupper($field->name);
				if (!method_exists($entity, $func)) {
					throw new \exception(vartype($entity)." does not support function $func as defined by {$scheme->tagName}.{$field->name}");
				}
				$value = $element->getAttribute($field->tag);
				if ($value !== null) {
					if ($field->type == "&") {
						$entity->$func($value);
					} else {
						$entity->$func($this->findEntity($value));
					}
				}
			}
		}
		
		//Perform specific decoding for this entity if applicable.
		$specificName = "decode".str_replace("\\", "", get_class($entity));
		if (method_exists($this, $specificName)) {
			$this->$specificName($entity, $element);
		}
	}
	
	protected function decodeAnalysis(\Analysis\Node\Node $analysis, Coder\Element $element)
	{
		switch ($element->getName()) {
			case "binding": {
				if ($t = $element->getAttribute("target")) {
					if (preg_match('/^builtin:(.*)/', $t, $matches)) {
						$analysis->binding->target = \Type\Builtin::makeWithName($matches[1]);
					} else {
						$analysis->binding->target = $this->findEntity($t);
					}
				}
			} break;
			case "type": {
				foreach ($element->getElements() as $e) {
					$type = $this->decodeType($e);
					$rel = $e->getAttribute('rel');
					if ($rel == "initial")  $analysis->type->initial  = $type;
					if ($rel == "inferred") $analysis->type->inferred = $type;
					//if ($rel == "required") $analysis->type->required = $type;
				}
			} break;
		}
	}
	
	public function decodeType(Coder\Element $element)
	{
		switch ($element->getName()) {
			case "type-builtin": return \Type\Builtin::makeWithName($element->getAttribute('name')); break;
			case "type-native": return \Type\Native::makeWithName($element->getAttribute('name')); break;
			case "type-generic": return \Type\Generic::make(); break;
			case "type-defined": return \Type\Defined::makeWithDefinition($this->findEntity($element->getAttribute('definition'))); break;
			case "type-func": {
				$input  = null;
				$output = null;
				foreach ($element->getElements() as $member) {
					switch ($member->getAttribute("rel")) {
						case "input":  $input  = $this->decodeType($member); break;
						case "output": $output = $this->decodeType($member); break;
						default: {
							throw new \exception("Only types with relation ('rel') 'input' or 'output' supported within an analysis type");
						}
					}
				}
				return \Type\Func::makeWithArgs($input, $output);
			} break;
			case "type-tuple": {
				$fields = array();
				foreach ($element->getElements() as $field) {
					$fields[] = $this->decodeType($field);
				}
				return \Type\Tuple::makeWithFields($fields);
			} break;
		}
		throw new \exception("Unable to decode type \"{$element->getName()}\"");
	}
	
	protected function decodeEntityTypeDefinition(\Entity\TypeDefinition $entity, Coder\Element $element)
	{
		$members = array();
		$typeVars = array();
		foreach ($element->getElements() as $member) {
			if ($member->getName() == "member") {
				if ($id = $member->getAttribute("id")) {
					$members[] = $this->findEntity($id);
				} else {
					throw new \exception("Type member has no ID");
				}
			}
			else if ($member->getName() == "typevar") {
				if ($id = $member->getAttribute("id")) {
					$typeVars[] = $this->findEntity($id);
				} else {
					throw new \exception("Type typevar has no ID");
				}
			}
			else {
				throw new \exception("Only 'member' and 'typevar' tags are supported within a type definition");
			}
		}
		$entity->setMembers($members);
		$entity->setTypeVars($typeVars);
	}
	
	protected function decodeEntityBlock(\Entity\Block $entity, Coder\Element $element)
	{
		$stmts = array();
		foreach ($element->getElements() as $stmt) {
			if ($stmt->getName() != "stmt") {
				throw new \exception("Only 'stmt' tags are supported within a block");
			}
			if ($id = $stmt->getAttribute("id")) {
				$stmts[] = $this->findEntity($id);
			} else {
				throw new \exception("Block statement has no ID");
			}
		}
		$entity->setStmts($stmts);
	}
	
	protected function decodeEntityFuncTuple(\Entity\Func\Tuple $entity, Coder\Element $element)
	{
		$args = array();
		foreach ($element->getElements() as $arg) {
			if ($arg->getName() != "arg") {
				throw new \exception("Only 'arg' tags are supported within a function argument tuple.");
			}
			if ($id = $arg->getAttribute("id")) {
				$args[] = $this->findEntity($id);
			} else {
				throw new \exception("Function argument in tuple has no ID.");
			}
		}
		$entity->setArgs($args);
	}
	
	protected function decodeEntityExprCallTuple(\Entity\Expr\Call\Tuple $entity, Coder\Element $element)
	{
		$args = array();
		foreach ($element->getElements() as $arg) {
			if ($arg->getName() != "arg") {
				throw new \exception("Only 'arg' tags are supported within a call argument tuple.");
			}
			if ($id = $arg->getAttribute("id")) {
				$args[] = $this->findEntity($id);
			} else {
				throw new \exception("Call argument in tuple has no ID.");
			}
		}
		$entity->setArgs($args);
	}
	
	protected function decodeEntityExternalDeclaration(\Entity\ExternalDeclaration $entity, Coder\Element $element)
	{
		$declarations = array();
		foreach ($element->getElements() as $declaration) {
			if ($declaration->getName() != "declaration") {
				throw new \exception("Only 'declaration' tags are supported within an external declaration.");
			}
			if ($id = $declaration->getAttribute("id")) {
				$declarations[] = $this->findEntity($id);
			} else {
				throw new \exception("External declaration has no ID");
			}
		}
		$entity->setDeclarations($declarations);
	}
	
	protected function decodeEntityExprTypeSpec(\Entity\Expr\TypeSpec $entity, Coder\Element $element)
	{
		$args = array();
		foreach ($element->getElements() as $arg) {
			if ($arg->getName() != "arg") {
				throw new \exception("Only 'arg' tags are supported within a tpe specialization.");
			}
			if ($id = $arg->getAttribute("id")) {
				$args[] = $this->findEntity($id);
			} else {
				throw new \exception("Type specialization argument has no ID.");
			}
		}
		$entity->setArgs($args);
	}

	protected function decodeEntityTypeTypeVar(\Entity\Type\TypeVar $entity, Coder\Element $element)
	{
		$elements = $element->getElements();
		if (count($elements)) {
			$e = array_pop($elements);
			$type = $this->decodeType($e);
			echo "Typevar {$entity->getID()}: Decoded type {$type->toHumanReadableString()}\n";
			if (!$type) {
				throw new \RuntimeException("Unable to decode TypeVar type.");
			}
			$entity->setType($type);
		}
	}
}