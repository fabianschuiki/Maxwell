<?php
namespace LET;

class Type_AST extends Type
{
	public $asn;
	public $members;
	public $subscope;
	
	public function __construct(Scope $scope, \AST\TypeStmt $node)
	{
		$members  = array();
		$subscope = new Scope($scope, $this);
		
		foreach ($node->body->stmts as $stmt) {
			switch ($stmt->kind()) {
				case 'VarStmt': {
					$members[] = new TypeMember($stmt);
				} break;
				case 'FuncStmt': {
					$scope->add(new Func_AST($scope, $stmt, $this));
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
		
		$this->asn      = $node;
		$this->members  = $members;
		$this->scope    = $scope;
		$this->subscope = $subscope;
		
		$scope->add($this);
	}
	
	public function name()    { return $this->asn->name->text; }
	public function members() { return $this->members; }
}