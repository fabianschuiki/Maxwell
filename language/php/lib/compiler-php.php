<?php
namespace Compiler;
use \Parser\AST;

class Compiler
{
	//The root block that is to be compiled down to PHP.
	protected $rootBlock;
	
	//The compiled PHP code.
	public $code;
	
	public function __construct($rootBlock) {
		$this->rootBlock = $rootBlock;
	}
	
	/** Compiles the given root block down to PHP. */
	public function execute() {
		$this->code = $this->compileBlock($this->rootBlock)."\n";
	}
	
	/** Compiles the given block. */
	private function compileBlock($block) {
		$chunks = array();
		foreach ($block->statements as $s) {
			$l = $this->compileStatement($s);
			$chunks[] = is_array($l) ? implode("\n", $l) : $l;
		}
		return implode("\n\n", $chunks);
	}
	
	/** Compiles the given statement. */
	private function compileStatement($stmt) {
		if ($stmt instanceof \Parser\AST\FunctionStmt) {
			return $this->compileFunctionStmt($stmt);
		}
		if ($stmt instanceof \Parser\AST\ReturnStmt) {
			return $this->compileReturnStmt($stmt);
		}
		if ($stmt instanceof \Parser\AST\ExpressionStmt) {
			return $this->compileExpressionStmt($stmt);
		}
		
		//Obviously we are unable to compile this statement.
		return sprintf("/* unsupported statement: %s */", get_class($stmt));
	}
	
	/** Compiles the given function statement. */
	private function compileFunctionStmt($stmt) {
		$l = array();
		$l[] = 'function '.$stmt->name->text.'($in) {';
		$l[] = '$out = array();';
		$l[] = $this->compileBlock($stmt->function->body);
		$l[] = $stmt->name->text.'_return:';
		$l[] = 'return $out;';
		$l[] = '}';
		return $l;
	}
	
	/** Compiles the given return statement. */
	private function compileReturnStmt($stmt) {
		$l = array();
		$name = $stmt->function->statement->name->text;
		$l[] = '/* return from '.$name.' */';
		$i = 0;
		foreach ($stmt->exprs as $e) {
			$arg = $stmt->function->outputs[$i];
			$l[] = '$out[\''.$arg->name->text.'\'] = '.$this->compileExpression($e).';';
			$i++;
		}
		$l[] = 'goto '.$name.'_return;';
		return $l;
	}
	
	/** Compiles the given expression statement. */
	private function compileExpressionStmt($stmt) {
		$s = $this->compileExpression($stmt->expr);
		return trim(rtrim($s, ')'), '(').';';
	}
	
	/** Compiles the given expression. */
	private function compileExpression($expr) {
		if ($expr instanceof \Parser\AST\BinaryOperatorExpr) {
			$s  = '('.$this->compileExpression($expr->lhs);
			$s .= ' '.$expr->operator->text.' ';
			$s .= $this->compileExpression($expr->rhs).')';
			return $s;
		}
		if ($expr instanceof \Parser\AST\IdentifierExpr) {
			return $this->compileRef($expr->ref);
		}
		if ($expr instanceof \Parser\AST\VariableExpr) {
			return $this->compileVariableExpr($expr);
		}
		if ($expr instanceof \Parser\AST\FunctionCallExpr) {
			return $this->compileFunctionCallExpr($expr);
		}
		return '/* unknown expression '.get_class($expr).' */';
	}
	
	private function compileRef($ref) {
		if ($ref instanceof \Parser\AST\FunctionArg) {
			$function = $ref->function;
			if ($function->inputs && in_array($ref, $function->inputs)) {
				return '$in[\''.$ref->name->text.'\']';
			}
			if ($function->outputs && in_array($ref, $function->outputs)) {
				return '$out[\''.$ref->name->text.'\']';
			}
		}
		if ($ref instanceof \Parser\AST\VariableExpr) {
			return '$var_'.$ref->name->text.'_'.$ref->type->text;
		}
		return 'null/*unknown*/';
	}
	
	private function compileVariableExpr($expr) {
		$s = $this->compileRef($expr);
		if (!$expr->noinit)
			$s .= ' = null';
		return $s;
	}
	
	private function compileFunctionCallExpr($expr) {
		$args = array();
		foreach ($expr->arguments as $a) {
			$name = $a->name->text;
			if (!$name) {
			}
		}
		return 'null /* not yet able to call functions */';
	}
}
