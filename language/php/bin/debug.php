#!/usr/bin/php
<?php
require_once __DIR__.'/../lib/autoload.php';

error_reporting(E_ALL ^ E_NOTICE);

$issues = new IssueList;

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
$analyzer->issues = $issues;
$analyzer->nodes = $parser->nodes;
$analyzer->run();
if ($issues->isFatal()) {
	goto compiled;
}

$compiler = new Compiler;
$compiler->nodes = $analyzer->nodes;
$compiler->run();
$compiledPath = $file->path.'.c';
file_put_contents($compiledPath, $compiler->output);

compiled:
foreach ($issues->issues as $i) {
	echo "$i\n";
}

ob_start();
$tokens = $lexer->flatTokens;
$nodes  = $parser->nodes;
$scope  = $analyzer->scope;
require __DIR__.'/../lib/dump.html.php';
$html = ob_get_contents();
ob_end_clean();
file_put_contents($file->path.'.html', $html);

if (!$issues->isFatal()) {
	$executablePath = $file->path.'.out';
	passthru('gcc -O3 -o '.escapeshellarg($executablePath).' '.escapeshellarg($compiledPath));
	passthru('objdump -d '.escapeshellarg($executablePath).' > '.escapeshellarg($file->path.'.asm'));
	passthru(escapeshellarg($executablePath));
}