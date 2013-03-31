<?php
require_once __DIR__."/include.php";

// Initialize the repository.
$repo = new Repository(__DIR__."/repo");

// Register a source file.
$sourceId = $repo->registerSource("main.mw");
$repo->clearSource($sourceId);
echo "main.mw has ID $sourceId\n";

// Create a new entity in the source file.
$f1 = $repo->makeObject("FunctionDefinition", $sourceId);
echo "f1 has ID {$f1->getId()}\n";
$f1->setName("doSomething");
$repo->flush();

// Create a new identifier.
$ident = $repo->makeObject("IdentifierExpr", $sourceId, $f1->getId());
echo "ident has ID {$ident->getId()}\n";
$ident->setName("myName");
$repo->flush();

// Set the identifier as a child of the function.
$f1->setIdent($ident);
$repo->flush();

// Add some code.
$f1->setIndepDeclCode("void main() {}");
$repo->flush();