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
$ctx["annotate"]["bindings"] = true;

// Generate and store the output.
$path = __DIR__."/repo/pretty.mw";
$output = "";
foreach (scandir(__DIR__."/repo/objects/1") as $id) {
	if (is_numeric($id)) {
		$rid = "1.$id";
		$output .= "// $rid\n";
		$output .= $printer->formatRootObject($rid, $ctx)."\n\n";
	}
}
file_put_contents($path, trim($output));
