<?php
require_once __DIR__."/include.php";

$repo = new Repository(__DIR__."/repo");

$f1 = $repo->getObject("1.1");
$f1->print_fragmentStates();

$ident = $f1->getIdent();
$f1->print_fragmentStates();
$ident->print_fragmentStates();

$n = $ident->getName();
echo "ident name = $n\n";
$ident->print_fragmentStates();
echo "modifying name\n";
$ident->setName("helloSir");
$ident->print_fragmentStates();
$f1->print_fragmentStates();