<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/frontend");
$manager->push();

$analyzer = new Driver\Analyzer;
$analyzer->addEntityID(1);
$analyzer->run();

$manager->pop();

$issues->pop();
$issues->report();