<?php
namespace LET;

class BinaryOp_AST extends BinaryOp
{
	public $asn;
	public $op;
	public $lhs;
	public $rhs;
	public $args;
	
	public function __construct(Scope $scope, \AST\BinaryOpExpr $node)
	{
		parent::__construct();
		
		$lhs = Expr::make($scope, $node->lhs);
		$rhs = Expr::make($scope, $node->rhs);
		
		$args = new Tuple_Impl($scope, array($lhs, $rhs));
		$args->parent = $this;
		
		$this->asn   = $node;
		$this->op    = new Ident_Impl($scope, $node->op);
		$this->lhs   = $lhs;
		$this->rhs   = $rhs;
		$this->args  = $args;
		$this->scope = $scope;
	}
	
	public function callee() { return $this->op; }
	public function args()   { return $this->args; }
	
	//TODO: This is about the nastiest hack ever conceived. It ensures that after cloning, Ident nodes maintain their bind results.
	//There has to be a better way to do this. And this code might probably be better off in the default implementation of cloneInto.
	public function cloneInto(Scope $scope)
	{
		$clone = parent::cloneInto($scope);
		$pairs = array();
		$pairs[] = array($clone, $this);
		$visited = array();
		while (count($pairs) > 0) {
			list($a, $b) = array_shift($pairs);
			if (!$a instanceof Node || !$b instanceof Node) continue;
			//echo "equalizing {$a->desc()} and {$b->desc()}\n";
			$visited[] = $a;
			$visited[] = $b;
			if ($a instanceof Ident && $b instanceof Ident) {
				//echo "-> equalizing idents!\n";
				$a->boundTo = $b->boundTo;
				$a->boundNodes = $b->boundNodes;
				$a->lastConfirmedType = $b->lastConfirmedType;
			}
			foreach ($a as $key => $as) {
				if (!isset($b->$key)) continue;
				$bs = $b->$key;
				if (is_object($as) && is_object($bs) && !in_array($as, $visited, true) && !in_array($bs, $visited, true)) $pairs[] = array($as, $bs);
			}
		}
		return $clone;
	}
}