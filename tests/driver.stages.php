<?php
require_once __DIR__."/include.php";

// Create the repository.
$repo = new Repository(__DIR__."/repo");

// Create a list of stages.
$stages = array();
$stages[] = new Stage\BuildGraphStage($repo);
$stages[] = new Stage\BindIdentifiersStage($repo);
$stages[] = new Stage\ConfigureCallsStage($repo);
$stages[] = new Stage\EvaluateTypeExpressionsStage($repo);
$stages[] = new Stage\FindCallCandidatesStage($repo);
$stages[] = new Stage\CalculatePossibleTypesStage($repo);
$stages[] = new Stage\CalculateRequiredTypesStage($repo);
$stages[] = new Stage\CalculateActualTypesStage($repo);
$stages[] = new Stage\NarrowCallCandidatesStage($repo);
$stages[] = new Stage\SelectCallCandidateStage($repo);

// Find the next stage to be executed.
$next = null;
foreach ($stages as $stage) {
	if ($repo->getObjectStageState("1.1", $stage->getName()) === false) {
		$next = $stage;
		break;
	}
}
if (!$next) {
	echo "Nothing left to do!\n";
	exit(0);
}
echo "Will execute stage {$stage->getName()}\n";

// Execute the stage.
$next->run("1.1");

// Write the changes to disk.
echo "Flushing changes to disk\n";
$repo->flush();