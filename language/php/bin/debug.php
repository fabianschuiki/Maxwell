#!/usr/bin/php
<?php
require_once __DIR__.'/../lib/autoload.php';

$file = new SourceFile;
$file->path = $argv[1];
$file->load();

$lexer = new Lexer;
$lexer->file = $file;
$lexer->run();

$parser = new Parser;
$parser->tokens = $lexer->tokens;
$parser->run();

$analyzer = new Analyzer;
$analyzer->nodes = $parser->nodes;
$analyzer->run();

ob_start();
$tokens = $lexer->flatTokens;
$nodes  = $parser->nodes;
require __DIR__.'/../lib/dump.html.php';
$html = ob_get_contents();
ob_end_clean();
file_put_contents($file->path.'.html', $html);

$compiler = new Compiler;
$compiler->nodes = $parser->nodes;
$compiler->run();
file_put_contents($file->path.'.php', $compiler->output);
