<?php
require_once __DIR__."/include.php";

// Create the repository.
$repo = new Repository(__DIR__."/repo");

// Initialize the pretty printer.
$printer = new PrettyPrinter($repo);

// Assemble a context.
$ctx = array();
$ctx["annotate"]["selected-call"] = true;
$ctx["annotate"]["types"] = true;

// Generate and store the output.
$path = __DIR__."/repo/pretty.mw";
$output = "";
foreach (array("1.1", "1.2") as $id) {
	$output .= "// $id\n";
	$output .= $printer->formatRootObject($id, $ctx)."\n\n";
}
file_put_contents($path, trim($output));
