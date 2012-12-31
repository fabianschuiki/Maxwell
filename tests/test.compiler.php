<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/frontend");
$manager->push();

$ids = $manager->getEntityStore()->getEntityIDsInFile("$TEST_DIR/frontend.mw");

$compiler = new Driver\Compiler;
$compiler->addEntityIDs($ids);
$compiler->run();

$dumper = new Dumper\DebugHTML;
$dumper->addEntityIDs($ids);
$dumper->run();

$manager->pop();

$fatal = $issues->isFatal();
$issues->pop();
$issues->report();
exit($fatal ? 1 : 0);