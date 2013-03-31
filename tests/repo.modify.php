<?php
require_once __DIR__."/include.php";

// Initialize the repository.
$repo = new Repository(__DIR__."/repo");

// Fetch the function entity and read its name and code fragment.
$f1 = $repo->getObject("1.1");
echo "function name = ".$f1->getName()."\n";
echo "function code = ".$f1->getIndepDeclCode()."\n";

