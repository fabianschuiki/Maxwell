<?php
namespace Store;
use Coder;
use Source\File;
use Source\Range;

class EntitySerializer
{
	static public function serializeRootEntity(\Entity\RootEntity $entity)
	{
		$root = null;
		
		if ($entity instanceof \Entity\FunctionDefinition) {
			$root = new Coder\Element("function");
			$root->setAttribute('name', $entity->getName());
			$root->setAttribute('body', $entity->getBody()->getID());
			$root->setAttribute('scope', $entity->getScope()->getID());
			static::serializeEntity($entity->getBody(), $root);
			static::serializeScope($entity->getScope(), $root);
		}
		if ($entity instanceof \Entity\TypeDefinition) {
			$root = new Coder\Element("type");
			$root->setAttribute('name', $entity->getName());
			$root->setAttribute('scope', $entity->getScope()->getID());
			static::serializeScope($entity->getScope(), $root);
			if ($entity->getSuperType())
				$root->setAttribute('superType', $entity->getSuperType()->getText());
		}
		
		if ($root) {
			$root->setAttribute('id', $entity->getID());
			$root->setAttribute('range', $entity->getRange()->toString());
			$root->setAttribute('humanRange', $entity->getHumanRange()->toString());
			$root->setAttribute('file', $entity->getRange()->getFile()->getPath());
			foreach ($entity->getSiblingEntities() as $sibling) {
				$e = $root->makeElement('sibling');
				$e->setAttribute('id', $sibling->getID());
			}
			foreach ($entity->getKnownEntities() as $known) {
				$e = $root->makeElement('known');
				$e->setAttribute('id', $known->getID());
			}
		}
		else {
			throw new \exception("Unable to serialize root entity ".vartype($entity).".");
		}
		
		return $root;
	}
	
	static private function serializeEntity(\Entity\Entity $entity, Coder\Element $root)
	{
		if ($entity instanceof \Entity\Block) {
			$e = $root->makeElement("block");
			
			$headScope = $entity->getHeadScope();
			$tailScope = $entity->getTailScope();
			$e->setAttribute('scope-head', $headScope->getID());
			$e->setAttribute('scope-tail', $tailScope->getID());
			static::serializeScope($headScope, $root);
			if ($headScope != $tailScope) static::serializeScope($tailScope, $root);
			
			foreach ($entity->getStmts() as $s) {
				static::serializeStmtEntity($s, $root);
				$sr = $e->makeElement('stmt');
				$sr->setAttribute('id', $s->getID());
			}
		}
		
		if ($e) {
			$e->setAttribute('id', $entity->getID());
			$e->setAttribute('range', $entity->getRange()->toString());
		}
		else {
			throw new \exception("Unable to serialize entity ".vartype($entity).".");
		}
	}
	
	static private function serializeStmtEntity(\Entity\Stmt\Stmt $stmt, Coder\Element $root)
	{
		if ($stmt instanceof \Entity\Stmt\Expr) {
			$e = $root->makeElement("expr-stmt");
			$e->setAttribute('expr', $stmt->getExpr()->getID());
			static::serializeExprEntity($stmt->getExpr(), $root);
		}
		
		if ($e) {
			$e->setAttribute('id', $stmt->getID());
			$e->setAttribute('range', $stmt->getRange()->toString());
			if ($stmt->getHumanRange()) $e->setAttribute('humanRange', $stmt->getHumanRange()->toString());
		}
		else {
			throw new \exception("Unable to serialize statement entity ".vartype($stmt).".");
		}
	}
	
	static private function serializeExprEntity(\Entity\Expr\Expr $expr, Coder\Element $root)
	{
		if ($expr instanceof \Entity\Expr\Constant) {
			$e = $root->makeElement("constant");
			$e->setAttribute('type', $expr->getType());
			$e->setAttribute('value', $expr->getValue());
		}
		if ($expr instanceof \Entity\Expr\Identifier) {
			$e = $root->makeElement("identifier");
			$e->setAttribute('name', $expr->getName());
			$e->setAttribute('scope', $expr->getScope()->getID());
		}
		if ($expr instanceof \Entity\Expr\VarDef) {
			$e = $root->makeElement("var");
			$e->setAttribute('name', $expr->getName());
			$e->setAttribute('scope', $expr->getScope()->getID());
			if ($expr->getType()) {
				static::serializeExprEntity($expr->getType(), $root);
				$e->setAttribute('type', $expr->getType()->getID());
			}
			if ($expr->getInitial()) {
				static::serializeExprEntity($expr->getInitial(), $root);
				$e->setAttribute('initial', $expr->getInitial()->getID());
			}
		}
		
		if ($e) {
			$e->setAttribute('id', $expr->getID());
			$e->setAttribute('range', $expr->getRange()->toString());
			if ($expr->getHumanRange()) $e->setAttribute('humanRange', $expr->getHumanRange()->toString());
		}
		else {
			throw new \exception("Unable to serialize expression entity ".vartype($expr).".");
		}
	}
	
	static private function serializeScope(\Entity\Scope\Scope $scope, Coder\Element $root)
	{
		if ($scope instanceof \Entity\Scope\ScopeDeclaration) {
			$e = $root->makeElement('scope-declaration');
			$e->setAttribute('declares', $scope->getDeclares()->getID());
		}
		else {
			$e = $root->makeElement('scope');
		}
		
		if ($e) {
			$e->setAttribute('id', $scope->getID());
			if ($scope->getOuter()) $e->setAttribute('outer', $scope->getOuter()->getID());
			if ($scope->getUpper()) $e->setAttribute('upper', $scope->getUpper()->getID());
		}
		else {
			throw new \exception("Unable to serialize scope ".vartype($scope).".");
		}
	}
	
	
	
	/*
	 * DECODING
	 */
	
	static public function decodeScaffolding(Coder\Element $element)
	{
		$e = null;
		switch ($element->getName()) {
			case 'function': $e = new \Entity\FunctionDefinition; break;
			case 'type':     $e = new \Entity\TypeDefinition; break;
			
			case 'block':    $e = new \Entity\Block; break;
			case 'scope':    $e = new \Entity\Scope\Scope; break;
			case 'scope-declaration': $e = new \Entity\Scope\ScopeDeclaration; break;
			
			case 'expr-stmt': $e = new \Entity\Stmt\Expr; break;
			case 'var': $e = new \Entity\Expr\VarDef; break;
			case 'identifier': $e = new \Entity\Expr\Identifier; break;
			case 'constant': $e = new \Entity\Expr\Constant; break;
		}
		if ($e) {
			if ($id = $element->getAttribute('id'))
				$e->setID($id);
			else
				throw new \exception("Element has no id: ".$this->encode($element));
		} else {
			throw new \exception("Unable to decode scaffolding for element '{$element->getName()}'.");
		}
		return $e;
	}
	
	static public function decodeRootEntity(Coder\Element $root)
	{
		$entity = static::decodeScaffolding($root);
		if (!$entity) return null;
		
		//Decode the barebone versions of the entities and store them in an ID map.
		$entities = array();
		$elements = array();
		foreach ($root->getElements() as $element) {
			if ($element->getName() == 'sibling' || $element->getName() == 'known') continue;
			$e = static::decodeScaffolding($element);
			$entities[$e->getID()] = $e;
			$elements[$e->getID()] = $element;
		}
		
		//Decode the child entities.
		$file = new File($root->getAttribute('file'));
		static::decodeEntity($entity, $root, $entities, $file);
		foreach ($entities as $id => $e) {
			static::decodeEntity($e, $elements[$id], $entities, $file);
		}
		
		return $entity;
	}
	
	static public function decodeRootEntityExternals(\Entity\RootEntity $entity, Coder\Element $root, EntityStore $store)
	{
		$siblings = array();
		$known = array();
		foreach ($root->getElements() as $e) {
			if ($e->getName() == 'sibling') $siblings[] = $store->getEntity($e->getAttribute('id'));
			if ($e->getName() == 'known')   $known[]    = $store->getEntity($e->getAttribute('id'));
		}
		
		$entity->setSiblingEntities($siblings);
		$entity->setKnownEntities($known);
	}
	
	static public function decodeEntity(\Entity\Node $entity, Coder\Element $root, array &$entities, File $file)
	{
		if ($entity instanceof \Entity\FunctionDefinition) {
			$entity->setName($root->getAttribute('name'));
			$entity->setBody($entities[$root->getAttribute('body')]);
			$entity->setScope($entities[$root->getAttribute('scope')]);
			$entity->setFile($file);
		}
		else if ($entity instanceof \Entity\Block) {
			$entity->setHeadScope($entities[$root->getAttribute('scope-head')]);
			$entity->setTailScope($entities[$root->getAttribute('scope-tail')]);
		}
		else if ($entity instanceof \Entity\Scope\Scope) {
			if ($o = $root->getAttribute('outer')) $entity->setOuter($entities[$o]);
			if ($u = $root->getAttribute('upper')) $entity->setUpper($entities[$u]);
		}
		else if ($entity instanceof \Entity\Stmt\Expr) {
			$entity->setExpr($entities[$root->getAttribute('expr')]);
		}
		else if ($entity instanceof \Entity\Expr\VarDef) {
			$entity->setName($root->getAttribute('name'));
			$entity->setScope($entities[$root->getAttribute('scope')]);
			if ($t = $root->getAttribute('type')) $entity->setType($entities[$t]);
			if ($i = $root->getAttribute('initial')) $entity->setInitial($entities[$i]);
		}
		else if ($entity instanceof \Entity\Expr\Identifier) {
			$entity->setName($root->getAttribute('name'));
			$entity->setScope($entities[$root->getAttribute('scope')]);
		}
		else if ($entity instanceof \Entity\Expr\Constant) {
			$entity->setType($root->getAttribute('type'));
			$entity->setValue($root->getAttribute('value'));
		}
		else {
			throw new \exception("Don't know how to decode ".vartype($entity).".");
		}
		
		//Decode the ranges where appropriate.
		if ($r = $root->getAttribute('range'))      $entity->setRange(Range::fromString($r, $file));
		if ($r = $root->getAttribute('humanRange')) $entity->setHumanRange(Range::fromString($r, $file));
	}
}