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
		$o .= "int main() { func_main__(); return 0; }\n";
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
	
	private $funcDefIndices = array();
	private function compileFuncDef(Node &$node)
	{
		$c = array();
		
		$name = 'func_';
		$name .= $this->makeCIdent($node->name->text);
		/*$name .= '_';
		foreach ($node->in as $i) {
			$name .= '_'.$i->type->text;
		}
		$name .= '_';
		foreach ($node->out as $o) {
			$name .= '_'.$o->type->text;
		}*/
		if (isset($this->funcDefIndices[$name])) {
			$name .= '_'.$this->funcDefIndices[$name]++;
		} else {
			$this->funcDefIndices[$name] = 1;
		}
		$node->c_name = $name;
		
		if (count($node->out)) {
			$node->c_retname = "{$name}_t";
			$type  = "typedef struct {\n";
			foreach ($node->out as $o) {
				$type .= "\t{$o->type->text}_t* {$o->name->text};\n";
			}
			$type .= "} {$node->c_retname};";
			$c[] = $type;
		} else {
			$node->c_retname = "void";
		}
		
		$ins = array();
		foreach ($node->in as $i) {
			$ins[] = "{$i->type->text}_t* {$i->name->text}";
		}
		$f  = "{$node->c_retname} {$node->c_name} (".implode(", ", $ins).")\n";
		$f .= $this->compileBlock($node->body);
		$c[] = $f;
		return $c;
	}
	
	private function compileTypeDef(Node &$node)
	{
		$n = "type_{$node->name->text}";
		$t  = "Type_t $n = type_make(\"{$node->name->text}\");\n";
		$t .= "typedef struct {\n";
		$t .= "\tType_t * isa; /* = &$n */\n";
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
		
		if ($node->a_target->c_retname != 'void') {
			$tmp = tmp();
			$call = "{$node->a_target->c_retname} $tmp = ";
		} else {
			$tmp = '';
			$call = "";
		}
		$call .= $node->a_target->c_name.'(';
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
		$c[] = "{$node->c_name}.isa = &type_{$node->type->text}";
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
	
	private function makeCIdent($text)
	{
		$r = '';
		for ($i = 0; $i < strlen($text); $i++) {
			$c = $text[$i];
			if (strpos("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_", $c) === false) {
				$c = sprintf('%02x', ord($c));
			}
			$r .= $c;
		}
		return $r;
	}
}
