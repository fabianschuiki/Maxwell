<?php

function tmp()
{
	global $tmpidx;
	if (!isset($tmpidx))
		$tmpidx = 0;
	return '_tmp'.$tmpidx++;
}

class Compiler
{
	public $nodes;
	public $output;
	
	public function run()
	{
		$o  = "/* automatically compiled on ".date('c')." */\n\n";
		$o .= file_get_contents(__DIR__.'/runtime.c');
		$o .= "\n// --- runtime end ---\n\n";
		$cn = $this->compileNodes($this->nodes);
		foreach ($cn as $n) {
			$o .= "$n\n\n";
		}
		$o .= "// --- debugging code ---\n";
		$o .= "void main() { func_main(); }\n";
		$this->output = $o;
	}
	
	private function compileNodes(array &$nodes)
	{
		$c = array();
		foreach ($nodes as $node) {
			$c = array_merge($c, $this->compileNode($node));
		}
		return $c;
	}
	
	private function compileNode(Node &$node)
	{
		switch ($node->kind) {
			case 'def.func':  return $this->compileFuncDef($node); break;
			case 'expr.call': return $this->compileCallExpr($node); break;
			case 'expr.var':  return $this->compileVarExpr($node); break;
			case 'expr.const.numeric': return $this->compileConstExpr($node); break;
			case 'expr.ident': return array('v'.$node->name); break;
		}
		return array("/*{$node->kind}*/");
	}
	
	private function compileFuncDef(Node &$node)
	{
		/*$c  = 'typedef struct {} func_'.$node->name->text.'_ret;';
		$c .= "\n";*/
		$f  = 'void func_';
		$f .= $node->name->text;
		$f .= "()\n";
		$f .= $this->compileBlock($node->body);
		return array($f);
	}
	
	private function compileCallExpr(Node &$node)
	{
		$c = array();
		$args = array();
		foreach ($node->args as $arg) {
			$cn = $this->compileNode($arg->expr);
			$args[] = '&'.array_pop($cn);
			$c = array_merge($c, $cn);
		}
		
		$tmp = tmp();
		$call  = 'int '.$tmp.' = '.$node->callee->name.'(';
		$call .= implode(', ', $args);
		$call .= ')';
		$c[] = $call;
		$c[] = $tmp;
		return $c;
	}
	
	private function compileVarExpr(Node &$node)
	{
		$c = array();
		$node->c_name = 'v'.$node->name->text;
		$c[] = $node->type->text.' '.$node->c_name;
		$c[] = $node->c_name;
		return $c;
	}
	
	private function compileConstExpr(Node &$node)
	{
		$n = tmp();
		$c = array();
		$c[] = 'int '.$n.' = '.$node->value->text;
		$c[] = $n;
		return $c;
	}
	
	private function compileBlock(Node &$node)
	{
		$s = "{";
		$cn = $this->compileNodes($node->nodes);
		foreach ($cn as $n) {
			$s .= "\n\t$n;";
		}
		$s .= "\n}";
		return $s;
	}
}
