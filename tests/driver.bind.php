<?php
require_once __DIR__."/include.php";

// Create the repository.
$repo = new Repository(__DIR__."/repo");

// Perform the stage.
$graph = new Stage\BuildGraphStage($repo);
$graph->run("1.1");
$bind = new Stage\BindIdentifiersStage($repo);
$bind->run("1.1");
$bind = new Stage\ConfigureCallsStage($repo);
$bind->run("1.1");

// Write the changes to disk.
$repo->flush();