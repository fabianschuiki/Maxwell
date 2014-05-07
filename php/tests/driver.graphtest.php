<?php
require_once __DIR__."/include.php";

// Create the repository.
$repo = new Repository(__DIR__."/repo");

// Perform the stage.
$f1 = $repo->getObject("1.1");
$ref = $f1->getInputs()->getGraphPrev();
echo "{$ref->describe()}\n";

echo "Accessing the reference\n";
$dst = $ref->get();
echo "{$ref->describe()}\n";