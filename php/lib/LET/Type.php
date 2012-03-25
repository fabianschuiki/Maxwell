<?php
namespace LET;

class Type extends Node
{
	private $asn;
	public $scope;
	
	public function __construct(\AST\TypeStmt $node)
	{
		$this->asn   = $node;
		$this->scope = new Scope;
		foreach ($node->stmts as $stmt) {
			switch ($stmt->type()) {
				case 'VarStmt': {
					$this->scope->add(new TypeMember($stmt));
				} break;
				default: {
					global $issues;
					$issues[] = new \Issue(
						'warning',
						"{$stmt->nice()} is not allowed inside type '{$node->name}'. Ignored.",
						$stmt,
						$node->name
					);
				} break;
			}
		}
	}
	
	public function __get($name)
	{
		switch ($name) {
			case 'name': return $this->asn->name->text; break;
		}
		return null;
	}
	
	public function details()
	{
		return "'{$this->name}'";
	}
}