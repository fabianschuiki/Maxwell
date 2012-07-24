<?php
require_once __DIR__."/include.php";

$issues = new IssueList;
$issues->push();

$manager = new Store\Manager("$TEST_OUTPUT_DIR/frontend");
$manager->push();
$tokenStore = $manager->getTokenStore();
$entityStore = $manager->getEntityStore();


$file = $manager->getSourceFileAtPath("$TEST_DIR/frontend.mw");

$lexer = new Lexer\Lexer($file);
$lexer->run();
$issues->reportAndExitIfFatal();
$tokenStore->setTokensForFile($lexer->getTokens(), $lexer->getFile());

$parser = new Parser\Parser($tokenStore->getTokensForFile($file));
$parser->run();
$issues->reportAndExitIfFatal();

$entitializer = new Entitializer($parser->getNodes(), $lexer->getFile());
$entitializer->run();
$issues->reportAndExitIfFatal();

$entities = $entitializer->getEntities();
foreach ($entities as $e) {
	$entityStore->setEntity($e);
}

$manager->pop();

$issues->pop();
$issues->report();