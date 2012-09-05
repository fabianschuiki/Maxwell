<?php
namespace Store;
use Coder;

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
}