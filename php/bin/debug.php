#!/usr/bin/php
<?php
require_once __DIR__.'/../lib/autoload.php';

error_reporting(E_ALL ^ E_NOTICE);

$args = array();
$opt_link = true;
foreach ($argv as $arg) {
	if ($arg[0] == '-') {
		switch ($arg) {
			case '-c': $opt_link = false; break;
		}
	} else {
		$args[] = $arg;
	}
}
$argv = $args;

$issues = new IssueList;

$file = new SourceFile;
$file->path = $argv[1];
$file->load();

if (count($argv) >= 3) {
	$outdir = $argv[2];
} else {
	$outdir = dirname($file->path).'/build';
}
if (!file_exists($outdir)) {
	mkdir($outdir);
}
$out = $outdir.'/'.basename($file->path, '.mw');

$lexer = new Lexer;
$lexer->file = $file;
$lexer->run();

$parser = new Parser;
$parser->tokens = $lexer->tokens;
$parser->run();

//Resolve the imports.
$importScope = new Scope;
$importIncludes = "#include \"".basename($out).".h\"\n";
foreach ($parser->nodes as $node)
{
	if ($node->kind != 'def.import') continue;
	$path = dirname($file->path)."/{$node->name}.mw";
	$outpath = "$outdir/{$node->name}";
	$scope_path = "$outpath.scope";
	if (!file_exists($scope_path) || filemtime($scope_path) < filemtime($path)) {
		$cmd = escapeshellarg($argv[0]).' -c '.escapeshellarg($path).' '.escapeshellarg($outdir);
		$result = 0;
		passthru($cmd, $result);
		if ($result != 0) {
			exit;
		}
	}
	$scope = Scope::unserialize(file_get_contents($scope_path));
	foreach ($scope->names as $name => $n) {
		echo "imported \033[1m$name\033[0m {$node->kind}\n";
		if (isset($importScope->names[$name]) && $importScope->names[$name]->kind == 'a.funcgrp') {
			$importScope->names[$name]->funcs = array_merge($importScope->names[$name]->funcs, $n->funcs);
		} else {
			$importScope->names[$name] = $n;
		}
	}
	$importIncludes .= "#include \"{$node->name}.h\"\n";
}

echo "\033[1mcompiling {$file->path}\033[0m...\n";

$analyzer = new Analyzer;
$analyzer->importScope = $importScope;
$analyzer->issues = $issues;
$analyzer->nodes = $parser->nodes;
$analyzer->run();
if ($issues->isFatal()) {
	goto compiled;
}

//Dump the scope.
file_put_contents("$out.scope", $analyzer->scope->serialize());

$compiler = new Compiler;
$compiler->issues = $issues;
$compiler->nodes = $analyzer->nodes;
$compiler->run();
file_put_contents("$out.c", $importIncludes.$compiler->output);
file_put_contents("$out.h", $compiler->header);

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
file_put_contents("$out.html", $html);

if ($issues->isFatal()) {
	exit -1;
}

$sa_out_o   = escapeshellarg("$out.o");
$sa_out_c   = escapeshellarg("$out.c");
$sa_out_asm = escapeshellarg("$out.asm");
passthru("gcc -c -O3 -o $sa_out_o $sa_out_c");
passthru("objdump -d $sa_out_o > $sa_out_asm");

//Compile the runtime if required.
$runtime_o   = "$outdir/runtime.o";
$runtime_asm = "$outdir/runtime.asm";
$runtime_c   = __DIR__.'/../lib/runtime.c';
$sa_runtime_o   = escapeshellarg($runtime_o);
$sa_runtime_asm = escapeshellarg($runtime_asm);
$sa_runtime_c   = escapeshellarg($runtime_c);
if (!file_exists($runtime_o)) {
	echo "\033[1mcompiling runtime\033[0m...\n";
	passthru("gcc -c -O3 -o $sa_runtime_o $sa_runtime_c");
	passthru("objdump -d $sa_runtime_o > $sa_runtime_asm");
}

//Link the final executable if so requested.
if ($opt_link) {
	echo "\033[1mlinking\033[0m...\n";
	$files = array();
	$dirs = array($outdir);
	while (count($dirs)) {
		$dirpath = array_pop($dirs);
		$dir = opendir($dirpath);
		if ($dir) {
			while ($dirent = readdir($dir)) {
				if ($dirent[0] == '.') continue;
				$direntpath = $dirpath.'/'.$dirent;
				if (is_dir($direntpath)) {
					array_push($dirs, $direntpath);
				} else if (substr($dirent, -2) == '.o') {
					$files[] = escapeshellarg($direntpath);
				}
			}
			closedir($dir);
		}
	}
	passthru("gcc -o ".escapeshellarg($out)." ".implode(' ', $files));
}
