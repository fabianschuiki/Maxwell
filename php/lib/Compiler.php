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
	public $header;
	
	private $mainRef = null;
	private $mainTakesArgs = false;
	private $preheader;
	private $postheader;
	private $usedTypes;
	
	public function run()
	{
		$h  = "/* automatically compiled on ".date('c')." */\n";
		$c  = $h."\n";
		$h .= "#pragma once\n";
		$h .= "#include \"".__DIR__.'/runtime.h'."\"\n\n";
		
		$this->preheader  = array();
		$this->postheader = array();
		$this->usedTypes  = array();
		
		//Compile each node.
		$hm = "";
		foreach ($this->nodes as $n) {
			$seg = $this->compileNode($n);
			if ($seg->stmts) {
				if ($seg->comment) {
					$c .= "//{$seg->comment}\n";
				}
				$c .= implode("\n", $seg->stmts)."\n\n";
			}
			if ($seg->hstmts) {
				if ($seg->comment) {
					$hm .= "//{$seg->comment}\n";
				}
				$hm .= implode("\n", $seg->hstmts)."\n\n";
			}
		}
		
		$structs = array();
		foreach ($this->usedTypes as $type) {
			$structs[] = "struct $type;";
		}
		$this->postheader = array_merge($structs, $this->postheader);
		
		$hparts = array();
		if (count($this->preheader))  $hparts[] = implode("\n", $this->preheader);
		$hparts[] = rtrim(trim($hm));
		if (count($this->postheader)) $hparts[] = implode("\n", $this->postheader);
		$h .= implode("\n\n", $hparts)."\n";
		
		if ($this->mainRef) {
			$c .= "// --- main function call ---\n";
			$c .= "int main(int argc, char * argv[])\n";
			$c .= "{\n";
			if ($this->mainTakesArgs) {
				$c .= "\t".trim("
	StringArray_t args;
	int i;
	for (i = 0; i < argc; i++) {
		String_t* arg = malloc(sizeof(*arg));
		arg->v = argv[i];
		func_add_28a3aStringArray2c20v3aString292d3e2829(&args, arg);
	}
				")."\n";
				$mainArg = "&args";
			}
			$c .= "\t{$this->mainRef}($mainArg);\n";
			$c .= "\treturn 0;\n";
			$c .= "}\n";
		}
		
		$this->output = $c;
		$this->header = $h;
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
		if ($node->c_ignore) {
			return null;
		}
		$fn = 'compile'.str_replace(' ', '', ucwords(str_replace('.', ' ', $node->kind)));
		if (method_exists($this, $fn)) {
			return call_user_func(array($this, $fn), $node);
		}
		
		switch ($node->kind) {
			case 'def.func':  return $this->compileFuncDef($node);  break;
			case 'def.type':  return $this->compileTypeDef($node);  break;
			case 'expr.call': return $this->compileCallExpr($node); break;
			//case 'expr.var':  return $this->compileVarExpr($node);  break;
			/*case 'expr.const.numeric': return $this->compileConstExpr($node); break;
			case 'expr.ident': return array($node->a_target->c_name); break;
			case 'stmt.if': return $this->compileIfStmt($node); break;
			case 'stmt.for': return $this->compileForStmt($node); break;*/
		}
		//return array("/*{$node->kind}*/");
		trigger_error("compileNode not implemented for {$node->kind}");
		return null;
	}
	
	private function compileStmtExpr(Node &$node)
	{
		$seg = new CSegment;
		$e = $this->compileNode($node->expr);
		$seg->stmts = $e->stmts;
		if ($e->expr && !$e->exprIsRef) {
			$seg->stmts[] = $e->expr.';';
		}
		return $seg;
	}
	
	private function compileStmtInline(Node &$node)
	{
		$seg = new CSegment;
		preg_match_all('/@(.+?)@/', $node->code, $matches);
 		$subs = array();
 		foreach ($matches[1] as $n) {
			$sn = $node->a_scope->find($n);
			if (!$sn) {
				$this->issues[] = new Issue(
					'error',
					"Name '$n' in inline C code unknown.",
					$node->range
				);
				return null;
			}
			$ref = $sn->c_ptr;
			if (!$ref) {
				$this->issues[] = new Issue(
					'error',
					"Identifier '$n' cannot be referenced in inline C code.",
					$node->range,
					array($sn->range)
				);
				return null;
			}
			$subs["@$n@"] = $ref; 
		}
		$seg->stmts[] = str_replace(array_keys($subs), array_values($subs), $node->code);
		return $seg;
	}
	
	private $funcDefIndices = array();
	private function compileFuncDef(Node &$node)
	{
		//If the function is generic, compile its incarnations instead.
		if ($node->a_generic) {
			$seg = new CSegment;
			$seg->comment = "Incarnations of generic function {$node->name->text}";
			foreach ($node->a_incarnations as $inc) {
				assert($inc->inc_func);
				$c = $this->compileFuncDef($inc->inc_func);
				$seg->add($c);
			}
			return $seg;
		}
		
		$seg = new CSegment;
		$seg->comment = "Definition of function {$node->name->text}";
		
		//Assemble the function name, potentially appending indices to create unique names.
		/*$name = 'func_'.static::makeCIdent($node->name->text);
		if (isset($this->funcDefIndices[$name])) {
			$name .= '_'.$this->funcDefIndices[$name]++;
		} else {
			$this->funcDefIndices[$name] = 1;
		}
		$node->c_name = $name;*/
		$name = $node->c_name;
		if ($node->name->text == 'main') {
			$this->mainRef = $node->c_name;
			if (count($node->in)) {
				$this->mainTakesArgs = true;
			}
		}
		
		//Synthesize the return type.
		if (count($node->out)) {
			$retname = "{$name}_t";
			$node->c_retname = $retname;
			$type = "typedef struct {\n";
			foreach ($node->out as $o) {
				$o->c_ref = $o->name->text;
				$type .= "\t{$o->a_target->c_ref} {$o->c_ref};\n";
				$o->c_ref = '_ret.'.$o->c_ref;
				$o->c_ptr = ($o->a_target->primitive ? '&'.$o->c_ref : $o->c_ref);
			}
			$type .= "} $retname;";
			$seg->hstmts[] = $type;
		} else {
			$retname = "void";
		}
		
		//Synthesize the function defintion.
		$ins = array();
		foreach ($node->in as $i) {
			$i->c_ref = $i->name->text;
			$i->c_ptr = ($i->a_target->primitive ? '&'.$i->c_ref : $i->c_ref);
			$type = $i->a_target->c_name;
			if (!$i->a_target->builtin && !in_array($type, $this->usedTypes)) {
				$this->usedTypes[] = $type;
			}
			if (!$i->a_target->primitive) {
				$type = "struct $type*";
			}
			$ins[] = "{$type} {$i->c_ref}";
		}
		$def  = "$retname {$node->c_name} (".implode(", ", $ins).")";
		$this->postheader[] = $def.';';
		$def .= "\n";
		if ($retname != 'void')	$def .= "{\n\t$retname _ret;\n";
		$def .= $this->compileBlock($node->body);
		if ($retname != 'void') $def .= "\n\treturn _ret;\n}";
		$seg->stmts[] = $def;
		return $seg;
	}
	
	private function compileTypeDef(Node &$node)
	{
		$name = static::makeCIdent($node->name->text);
		//$node->c_name = "{$name}_t";
		$node->c_ref = $node->c_name;
		if (!$node->primitive) {
			$node->c_ref .= '*';
		}
		
		$struct = "struct {$node->c_name}";
		$this->preheader[] = $struct.';';
		$typedef  = "typedef $struct {\n";
		$typedef .= "\tType_t * isa /* = &type_$name*/;\n";
		
		foreach ($node->nodes as $n) {
			$typeNode = $n->a_target;
			$type = $typeNode->c_name;
			if (!$typeNode->primitive) {
				$type = "struct $type*";
			}
			$n->c_name = static::makeCIdent(strval($n->name));
			$n->c_ref  = $n->c_name;
			$typedef .= "\t$type {$n->c_name};\n";
		}
		
		$typedef .= "} {$node->c_name};";
		
		$seg = new CSegment;
		$seg->comment = "Definition of type {$node->name->text}";
		$seg->stmts[] = "Type_t type_$name = type_make(\"{$node->name->text}\");";
		$seg->hstmts[] = $typedef;
		return $seg;
	}
	
	private function compileCallExpr(Node &$node)
	{
		$seg = new CSegment;
		$f = $node->a_target;
		
		//Assemble the list of arguments and the statements required to calculate them.
		$args = array();
		foreach ($node->args as $a) {
			$s = $this->compileNode($a->expr);
			$seg->add($s);
			assert($s->expr != null);
			$args[] = $s->expr;
		}
		
		//Shortcut for builtin operators.
		if ($f->builtin) {
			$seg->expr = "($args[0] {$f->name->text} $args[1])";
			return $seg;
		}
		
		//Assemble the function call.
		assert($f->c_name);
		$call = $f->c_name.'('.implode(', ', $args).')';
		
		//Depending on whether we have a return value or not the function call acts as an expression or a simple statement.
		if (isset($node->a_target->c_retname)) {
			$seg->expr = $call;
			$out = $f->a_types->out;
			if (count($out->fields) == 1) {
				$seg->expr .= '.'.$out->fields[0]->name;
			}
			if (count($f->out) > 1) {
				$this->issues[] = new Issue(
					'error',
					"Multiple return values not yet implemented.",
					$node->range
				);
				return null;
			}
		} else {
			$seg->stmts[] = "$call;";
		}
		return $seg;
	}
	
	private function compileExprVar(Node &$node)
	{
		$typeNode = $node->a_target;
		
		$name = "{$node->name->text}_{$node->a_scope->index}";
		$node->c_name = $name;
		$node->c_ref  = ($node->a_local && !$typeNode->primitive ? '&'.$name : $name);
		$node->c_ptr  = ($node->a_local ||  $typeNode->primitive ? '&'.$name : $name);
		
		$type = $node->a_target->c_name;
		if (!$node->a_local && !$typeNode->primitive) {
			$type .= '*';
		}
		
		$seg = new CSegment;
		$def = "$type $name";
		if (isset($node->initial)) {
			$i = $this->compileNode($node->initial);
			$seg->add($i);
			if ($i->expr) {
				$def .= ' = ';
				if ($node->a_local && !$typeNode->primitive) {
					$def .= '*';
				}
				$def .= $i->expr;
			}
		}
		
		$seg->stmts[] = "$def;";
		$seg->expr = $node->c_ref;
		$seg->exprIsRef = true;
		return $seg;
	}
	
	private function compileExprConstNumeric(Node &$node)
	{
		$seg = new CSegment;
		$seg->expr = $node->value->text;
		return $seg;
	}
	
	private function compileExprConstString(Node &$node)
	{
		$seg = new CSegment;
		$tmp = tmp();
		$seg->stmts[] = "String_t* $tmp = malloc(sizeof(String_t));";
		$seg->stmts[] = "{$tmp}->v = \"{$node->value}\";";
		$seg->expr = $tmp;
		return $seg;
	}
	
	private function compileExprIdent(Node &$node)
	{
		$seg = new CSegment;
		$seg->expr = $node->a_target->c_ref;
		return $seg;
	}
	
	private function compileExprTuple(Node &$node)
	{
		$seg = new CSegment;
		$exprs = array();
		foreach ($node->exprs as $expr) {
			$es = $this->compileNode($expr);
			$seg->add($es);
			$seg->stmts[] = $es->expr.";";
			$exprs[] = $es->expr;
		}
		$seg->expr = "/* tuple (".implode(', ', $exprs).") */";
		return $seg;
	}
	
	private function compileExprMember(Node &$node)
	{
		$seg = new CSegment;
		$expr = $this->compileNode($node->expr);
		$seg->add($expr);
		$seg->expr = "{$expr->expr}->{$node->a_target->c_ref}";
		return $seg;
	}
	
	private function compileBlock(Node &$node)
	{
		$stmts = array();
		foreach ($node->nodes as $n) {
			$seg = $this->compileNode($n);
			if (is_array($seg->stmts)) {
				$stmts[] = str_replace("\n", "\n\t", implode("\n", $seg->stmts));
			}
		}
		return "{\n\t".implode("\n\t", $stmts)."\n}";
	}
	
	private function compileStmtIf(Node &$node)
	{
		$seg = new CSegment;
		$condition = $this->compileNode($node->condition);
		$seg->add($condition);
		$stmt = "if ({$condition->expr}) ".$this->compileBlock($node->body);
		if (isset($node->else)) {
			$stmt .= ' else '.$this->compileBlock($node->else->body);
		}
		$seg->stmts[] = $stmt;
		return $seg;
		/*$c = $this->compileNode($node->condition);
		$s  = 'if ('.array_pop($c).') ';
		$s .= $this->compileBlock($node->body);
		if (isset($node->else)) {
			$s .= ' else '.$this->compileBlock($node->else->body);
		}
		$c[] = $s;
		return $c;*/
	}
	
	private function compileStmtFor(Node &$node)
	{
		$seg = new CSegment;
		$initial   = $this->compileNode($node->initial);
		$condition = $this->compileNode($node->condition);
		$step      = $this->compileNode($node->step);
		$body      = $this->compileBlock($node->body);
		
		$seg->add($initial);
		$stmts   = array();
		$stmts   = array_merge($stmts, $condition->stmts);
		$stmts[] = "if (!{$condition->expr}) break;";
		$stmts[] .= trim(rtrim($body, "}\n\t "), "{\n\t ");
		$stmts   = array_merge($stmts, $step->stmts);
		
		$stmt = "do {";
		foreach ($stmts as $s) {
			$stmt .= "\n\t$s";
		}
		$stmt .= "\n} while(1);";
		$seg->stmts[] = $stmt;
		
		return $seg;
		
		/*$c = $this->compileNode($node->initial);
		$s  = "do {\n\t";
		$ccn = $this->compileNode($node->condition);
		$cc = array_pop($ccn);
		$s .= implode(";\n\t", $ccn).";\n\t";
		$s .= "if (!$cc)\n\t\tbreak;\n\t";
		$s .= str_replace("\n", "\n\t", $this->compileBlock($node->body))."\n\t";
		$s .= implode(";\n\t", $this->compileNode($node->step)).";\n";
		$s .= "} while(1)";
		$c[] = $s;
		return $c;*/
	}
	
	static public function makeCIdent($text)
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