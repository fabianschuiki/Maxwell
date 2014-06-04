<?php

class Dump
{
	static public function ast(SourceFile $file, Lexer $lexer, Parser $parser)
	{
		ob_start();
		include __DIR__.'/Dump/ast.php';
		$html = ob_get_contents();
		ob_end_clean();
		return $html;
	}
	
	static public function let(\LET\Root $let)
	{
		ob_start();
		include __DIR__.'/Dump/let.php';
		$html = ob_get_contents();
		ob_end_clean();
		return $html;
	}
}