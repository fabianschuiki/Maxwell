<?php
require_once __DIR__."/include.php";

if (count($argv) < 2) {
	die("Not enough arguments.\n");
}
$path = $argv[1];
if (!file_exists($path)) {
	die("Input file $path does not exist.\n");
}

function separate($input, &$tree, &$main)
{
	foreach ($input as $key => $value) {
		if ($key === "class") {
			$tree[$key] = $value;
			//echo "storing $key in tree\n";
		} else {
			if (is_object($value) || is_array($value)) {
				$tree[$key] = array();
				$main[$key] = array();
				//echo "parsing $key\n";
				separate($value, $tree[$key], $main[$key]);
				if (is_object($input) && count($tree[$key]) == 0 && !is_array($value)) unset($tree[$key]);
				if (is_object($input) && count($main[$key]) == 0 && !is_array($value)) unset($main[$key]);
			} else {
				//echo "storing $key in main\n";
				$main[$key] = $value;
			}
		}
	}
}

// Parse the JSON file and split the "class" tags from the rest.
$input = json_decode(file_get_contents($path));
if ($input === null) {
	throw new InvalidArgumentException("JSON file at path $path is invalid. JSON error ".json_last_error().".");
}
if (!is_array($input)) {
	$input = array($input);
}
$names = array();
foreach ($input as $index => $data) {
	$class = null;
	if (isset($data->class)) {
		$class = $data->class;
	}
	unset($data->class);
	if (isset($data->name)) {
		$names["1.".($index+1)] = $data->name;
	}

	// Split up the rest of the data.
	$tree = array();
	$main = array();
	separate($data, $tree, $main);

	// Store the output in the repository.
	$path = __DIR__."/repo/objects/1/".($index+1);
	if (!file_exists($path)) {
		mkdir($path, 0777, true) or die("Unable to make directory $path.\n");
	}
	file_put_contents($path."/tree", json_encode($tree));
	file_put_contents($path."/main", json_encode($main));
	if ($class !== null) {
		file_put_contents($path."/class", $class);
	}
}
file_put_contents(__DIR__."/repo/objects/1/names-local", json_encode($names));