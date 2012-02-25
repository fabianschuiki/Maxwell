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
			if (strpos(trim($n), '/') === 0)
				$o .= "\n";
			$o .= "$n\n";
		}
		$o .= "\n// --- debugging code ---\n";
		$o .= "int main() { func_main(); return 0; }\n";
		$this->output = $o;
	}
	
	private function compileNodes(array &$nodes)
	{
		$c = array();
		foreach ($nodes as $node) {
			$c = array_merge($c, array("//{$node->kind}"), $this->compileNode($node));
		}
		return $c;
	}
	
	private function compileNode(Node &$node)
	{
		switch ($node->kind) {
			case 'def.func':  return $this->compileFuncDef($node); break;
			case 'def.type':  return $this->compileTypeDef($node); break;
			case 'expr.call': return $this->compileCallExpr($node); break;
			case 'expr.var':  return $this->compileVarExpr($node); break;
			case 'expr.const.numeric': return $this->compileConstExpr($node); break;
			case 'expr.ident': return array($node->a_target->c_name); break;
			case 'stmt.if': return $this->compileIfStmt($node); break;
			case 'stmt.for': return $this->compileForStmt($node); break;
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
	
	private function compileTypeDef(Node &$node)
	{
		$cls = "class_{$node->name->text}";
		$t  = "class_t $cls = (class_t){\"{$node->name->text}\"};\n";
		$t .= "typedef struct {\n";
		$t .= "\tclass_t * isa; /* = &$cls */\n";
		$t .= "\tint x, y;\n";
		$t .= "} {$node->name->text}_t;";
		return array($t);
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
		$node->c_name = "s{$node->a_scope->index}_{$node->name->text}";
		$s = "{$node->type->text}_t {$node->c_name}";
		if (isset($node->initial)) {
			$cn = $this->compileNode($node->initial);
			$n = array_pop($cn);
			$c = array_merge($c, $cn);
			$s .= ' = '.$n;
		}
		$c[] = $s;
		$c[] = "{$node->c_name}.isa = &class_{$node->type->text}";
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
			$n = str_replace("\n", "\n\t", $n);
			$s .= "\n\t$n;";
		}
		$s .= "\n}";
		return $s;
	}
	
	private function compileIfStmt(Node &$node)
	{
		$c = $this->compileNode($node->condition);
		$s  = 'if ('.array_pop($c).') ';
		$s .= $this->compileBlock($node->body);
		if (isset($node->else)) {
			$s .= ' else '.$this->compileBlock($node->else->body);
		}
		$c[] = $s;
		return $c;
	}
	
	private function compileForStmt(Node &$node)
	{
		$c = $this->compileNode($node->initial);
		$s  = "do {\n\t";
		$ccn = $this->compileNode($node->condition);
		$cc = array_pop($ccn);
		$s .= implode(";\n\t", $ccn).";\n\t";
		$s .= "if (!$cc)\n\t\tbreak;\n\t";
		$s .= str_replace("\n", "\n\t", $this->compileBlock($node->body))."\n\t";
		$s .= implode(";\n\t", $this->compileNode($node->step)).";\n";
		$s .= "} while(1)";
		$c[] = $s;
		return $c;
	}
}
