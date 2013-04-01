<?php
require_once __DIR__."/include.php";

// Initialize the repository.
$repo = new Repository(__DIR__."/repo");

// Fetch the function entity and modify something in the identifier.
$f1 = $repo->getObject("1.1");
print_r($f1);
$ident = $f1->getIdent();
$ident->setExprCode("Hello World");
$repo->flush();
