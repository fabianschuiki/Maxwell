#!/usr/bin/php
<?php
require_once __DIR__.'/../lib/autoload.php';

$lexer = new Lexer;
$lexer->input = file_get_contents($argv[1]);
$lexer->run();

$parser = new Parser;
$parser->tokens = $lexer->tokens;
$parser->run();

$sc = new SourceColorizer;
$sc->input  = $lexer->input;
$sc->flatTokens = $lexer->flatTokens;
$sc->colorize();

$template = file_get_contents(__DIR__.'/../lib/SourceColorizer.html');
file_put_contents($argv[1].'.html', str_replace(array('#title', '#body'), array(basename($argv[1]), $sc->output), $template));
