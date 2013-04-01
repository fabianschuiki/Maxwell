<?php
require_once __DIR__."/include.php";

$repo = new Repository(__DIR__."/repo");

$f1 = $repo->getObject("1.1");
$f1->print_fragmentStates();

/*$ident = $f1->getIdent();
$f1->print_fragmentStates();
$ident->print_fragmentStates();

$n = $ident->getName();
echo "ident name = $n\n";
$ident->print_fragmentStates();
echo "modifying name\n";
$ident->setName("helloSir");
$ident->print_fragmentStates();
$f1->print_fragmentStates();*/

$inner = $f1->getInner();
$inner->print_fragmentStates();
$f1->print_fragmentStates();
echo "inner.name = ".$inner->getName()."\n";
echo "inner.someText = ".$inner->getSomeText()."\n";

echo "modifying inner.someText\n";
$inner->setSomeText("hahaha");
$inner->print_fragmentStates();
$f1->print_fragmentStates();

$repo->flush();

/*$f1->setName("someFunc");
$f1->print_fragmentStates();

$f1->tree_dirty = true;
$repo->notifyObjectFragmentDirty($f1->getId(), "tree");
$f1->print_fragmentStates();

$repo->flush();*/