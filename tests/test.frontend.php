<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/frontend");
$manager->push();

$frontend = new Driver\Frontend;
$frontend->addFile("$TEST_DIR/frontend.mw");
$frontend->run();

$manager->pop();

$issues->pop();
$issues->report();