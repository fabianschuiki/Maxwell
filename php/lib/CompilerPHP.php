<?php

class Compiler
{
	public $nodes;
	public $output;
	public $scopeID = 0;
	
	public function run()
	{
		$this->output  = "#!/usr/bin/php\n<?php\n";
		$this->output .= "/** compiled on ".date("c")." */\n";
		$this->output .= "require_once '".__DIR__."/runtime.php';\n\n";
		foreach ($this->nodes as $n) {
			$this->output .= $this->compileNode($n).";\n\n";
		}
		$this->output .= "\$ret = array();\n";
		$this->output .= "main(null, \$ret);\n";
		$this->output .= "print_r(\$ret);\n";
		$this->output .= "echo(\"\\n\");\n";
	}
	
	private function compileNode(Node &$node)
	{
		if (isset($node->scope) && !isset($node->scope->c_name)) {
			$node->scope->c_name = 'scp_'.$this->scopeID++;
		}
		switch ($node->kind) {
			case 'def.func': {
				$node->c_name = $node->name->text;
				$c  = "function {$node->c_name}(\$in, &\$out)\n";
				$c .= $this->compileBlock($node->body);
				return $c;
			} break;
			case 'expr.op.binary': {
				$c  = $this->compileNode($node->lhs);;
				$c .= ' '.$node->op->text.' ';
				$c .= $this->compileNode($node->rhs);
				return "($c)";
			} break;
			case 'expr.var': {
				$node->c_name = '$v'./*$node->scope->c_name.'["'.*/$node->name->text/*.'"]'*/;
				return $node->c_name;
			} break;
			case 'expr.const.numeric': { return $node->value->text; } break;
			case 'expr.const.string':  { return '"'.$node->value->text.'"'; } break;
			case 'expr.ident':         { return $node->target->c_name; } break;
			case 'stmt.return': {
				$c  = '$out = '.$this->compileNode($node->expr);
				$c .= '; return';
				return $c;
			} break;
		}
		return "/*{$node->kind}*/";
	}
	
	private function compileBlock(Node &$node)
	{
		$c = "";
		foreach ($node->nodes as $n) {
			$c .= "\n".$this->compileNode($n).';';
		}
		return "{".str_replace("\n", "\n\t", $c)."\n}";
	}
}
