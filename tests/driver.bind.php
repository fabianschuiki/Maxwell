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
$bind = new Stage\EvaluateTypeExpressionsStage($repo);
$bind->run("1.1");
$bind = new Stage\FindCallCandidatesStage($repo);
$bind->run("1.1");
/*$bind = new Stage\CalculatePossibleTypesStage($repo);
$bind->run("1.1");
$bind = new Stage\CalculateRequiredTypesStage($repo);
$bind->run("1.1");
$bind = new Stage\CalculateActualTypesStage($repo);
$bind->run("1.1");
$bind = new Stage\NarrowCallCandidatesStage($repo);
$bind->run("1.1");
$bind = new Stage\SelectCallCandidateStage($repo);
$bind->run("1.1");*/

// Write the changes to disk.
echo "Flushing changes to disk\n";
$repo->flush();