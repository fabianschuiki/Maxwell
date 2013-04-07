<?php
require_once __DIR__."/include.php";

$forceStages = array_slice($argv, 1);

// Create the repository.
$repo = new Repository(__DIR__."/repo");

// Objects to be processed.
$objectIds = array();
foreach (scandir(__DIR__."/repo/objects/1") as $id) {
	if (is_numeric($id))
		$objectIds[] = "1.$id";
}

Stage\CalculatePossibleTypesStage::$verbosity = 99;
Stage\CalculateActualTypesStage::$verbosity = 99;

// Create a list of stages.
$stages = array();
$stages[] = new Stage\BuildGraphStage($repo);
$stages[] = new Stage\BindIdentifiersStage($repo);
$stages[] = new Stage\ConfigureCallsStage($repo);
$stages[] = new Stage\ConfigureAssumptionStatementsStage($repo);
$stages[] = new Stage\EvaluateTypeExpressionsStage($repo);
$stages[] = new Stage\FindCallCandidatesStage($repo);
$stages[] = new Stage\CalculatePossibleTypesStage($repo);
$stages[] = new Stage\CalculateRequiredTypesStage($repo);
$stages[] = new Stage\CalculateActualTypesStage($repo);
$stages[] = new Stage\NarrowCallCandidatesStage($repo);
$stages[] = new Stage\SelectCallCandidateStage($repo);

// Find the next stage to be executed.
$next = null;
$next_oid = null;
foreach ($stages as $stage) {
	foreach ($objectIds as $oid) {
		if ($repo->getObjectStageState($oid, $stage->getName()) === false || in_array($oid.".".$stage->getName(), $forceStages)) {
			$next = $stage;
			$next_oid = $oid;
			break;
		}
	}
	if ($next !== null)
		break;
}
if (!$next) {
	echo "Nothing left to do!\n";
	exit(0);
}
echo "Will execute stage \033[32;1m{$stage->getName()}\033[0m on $next_oid\n";

// Execute the stage.
$next->run($next_oid);

// Write the changes to disk.
echo "Flushing changes to disk\n";
$repo->flush();