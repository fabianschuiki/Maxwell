#!/usr/bin/php
<?php
require_once __DIR__.'/../lib/autoload.php';

$lexer = new Lexer;
$lexer->input = file_get_contents($argv[1]);
$lexer->run();

$sc = new SourceColorizer;
$sc->input  = $lexer->input;
$sc->tokens = $lexer->tokens; 
$sc->colorize();
file_put_contents($argv[1].'.html', '<html><head><title>'.basename($argv[1]).'</title></head><body>'.$sc->output.'</body></html>');
