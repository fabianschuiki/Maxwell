<?php
require_once __DIR__."/include.php";

// Create the repository.
$repo = new Repository(__DIR__."/repo");

// Initialize the pretty printer.
$printer = new PrettyPrinter($repo);

// Generate and store the output.
$path = __DIR__."/repo/pretty.mw";
file_put_contents($path, $printer->formatRootObject("1.1"));
