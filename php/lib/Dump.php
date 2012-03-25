<?php

class Dump
{
	static public function ast(SourceFile $file, Lexer $lexer, Parser $parser)
	{
		ob_start();
		require __DIR__.'/Dump/ast.php';
		$html = ob_get_contents();
		ob_end_clean();
		return $html;
	}
	
	static public function let(SourceFile $file, Analyzer $analyzer)
	{
		ob_start();
		require __DIR__.'/Dump/let.php';
		$html = ob_get_contents();
		ob_end_clean();
		return $html;
	}
}