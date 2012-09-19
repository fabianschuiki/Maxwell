<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/frontend");
$manager->push();

$ids = $manager->getEntityStore()->getEntityIDsInFile("$TEST_DIR/frontend.mw");

$analyzer = new Driver\Analyzer;
$analyzer->addEntityIDs($ids);
$analyzer->run();

$manager->pop();

$issues->pop();
$issues->report();