<?php
namespace Analyzer;
use \Parser\AST;

class Analyzer
{
	//The root block to be analyzed.
	protected $rootBlock;
	
	public function __construct($rootBlock) {
		$this->rootBlock = $rootBlock;
	}
	
	/** Analyzes the root block, extending its AST. */
	public function execute() {
		$this->analyzeBlock($this->rootBlock);
	}
	
	/** Analyzes the given block. */
	private function analyzeBlock($block, $scope = null) {
		$block->scope = ($scope ? $scope : new Scope);
		foreach ($block->statements as $stmt) {
			$stmt->block = $block;
			$this->analyzeStatement($stmt);
		}
	}
	
	/** Analyzes the given statement. */
	private function analyzeStatement($stmt) {
		if ($stmt instanceof \Parser\AST\FunctionStmt) {
			$scope = new Scope;
			$scope->parent = $stmt->block->scope;
			$stmt->function->statement = $stmt;
			$stmt->function->body->block = $stmt->block;
			$stmt->function->body->block->function = $stmt->function;
			foreach ($stmt->function->inputs as $input) {
				$input->function = $stmt->function;
				$scope->map[$input->name->text] = $input;
			}
			foreach ($stmt->function->outputs as $output) {
				$output->function = $stmt->function;
				$scope->map[$output->name->text] = $output;
			}
			$this->analyzeBlock($stmt->function->body, $scope);
		}
		if ($stmt instanceof \Parser\AST\ReturnStmt) {
			$block = $stmt->block;
			while ($block && !$block->function) {
				$block = $block->block;
			}
			$stmt->function = $block->function;
			foreach ($stmt->exprs as $e) {
				$e->scope = $stmt->block->scope;
				$this->analyzeExpression($e);
			}
		}
		if ($stmt instanceof \Parser\AST\ExpressionStmt) {
			$stmt->expr->scope = $stmt->block->scope;
			$this->analyzeExpression($stmt->expr);
		}
	}
	
	/** Analyzes the given expression. */
	private function analyzeExpression($expr) {
		if ($expr instanceof \Parser\AST\BinaryOperatorExpr) {
			$expr->lhs->scope = $expr->scope;
			$expr->rhs->scope = $expr->scope;
			if ($expr->operator->isSymbol('=') && $expr->lhs instanceof \Parser\AST\VariableExpr)
				$expr->lhs->noinit = true;
			$this->analyzeExpression($expr->lhs);
			$this->analyzeExpression($expr->rhs);
		}
		if ($expr instanceof \Parser\AST\IdentifierExpr) {
			$scope = $expr->scope;
			while ($scope && !($ref = $scope->map[$expr->identifier->text])) {
				$scope = $scope->parent;
			}
			$expr->ref = $ref;
		}
	}
}

class Scope
{
	public $parent;
	public $map = array();
}
