<?php
require_once __DIR__."/include.php";

// Initialize the repository.
$repo = new Repository(__DIR__."/repo");

// Register a source file.
$sourceId = $repo->registerSource("main.mw");
echo "main.mw has ID $sourceId\n";

// Create a new entity in the source file.
$f1 = $repo->makeObject("FunctionDefinition", $sourceId);
echo "f1 has ID {$f1->getId()}\n";
$f1->setName("doSomething");
$repo->flush();

// Add some code.
$f1->setIndepDeclCode("void main() {}");
$repo->flush();