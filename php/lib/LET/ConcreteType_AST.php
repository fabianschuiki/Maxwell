<?php
namespace LET;

class ConcreteType_AST extends ConcreteType
{
	public $asn;
	public $members;
	public $subscope;
	
	public function __construct(Scope $scope, \AST\TypeStmt $node)
	{
		parent::__construct();
		
		$members  = array();
		$subscope = new Scope($scope, $this);
		
		foreach ($node->body->stmts as $stmt) {
			switch ($stmt->kind()) {
				case 'VarStmt': {
					$members[] = new TypeMember_AST($scope, $stmt);
				} break;
				case 'FuncStmt': {
					new Func_AST($scope, $stmt, $this);
				} break;
				default: {
					global $issues;
					$issues[] = new \Issue(
						'warning',
						"{$stmt->nice()} is not allowed inside type '{$node->name}'. Ignored.",
						$stmt
					);
				} break;
			}
		}
		
		$parent = null;
		if ($node->parent) $parent = new TypeExpr($scope, Expr::make($scope, $node->parent));
		
		$this->asn      = $node;
		$this->members  = $members;
		$this->parent   = $parent;
		$this->scope    = $scope;
		$this->subscope = $subscope;
		
		$scope->add($this);
	}
	
	public function name()    { return $this->asn->name->text; }
	public function members() { return $this->members; }
	
	public function range()   { return $this->asn->name->range; }
}