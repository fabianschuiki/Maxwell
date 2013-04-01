<?php
require_once __DIR__."/include.php";

function separate($input, &$tree, &$main)
{
	foreach ($input as $key => $value) {
		if ($key === "class") {
			$tree[$key] = $value;
			echo "storing $key in tree\n";
		} else {
			if (is_object($value) || is_array($value)) {
				$tree[$key] = array();
				$main[$key] = array();
				echo "parsing $key\n";
				separate($value, $tree[$key], $main[$key]);
				if (is_object($input) && count($tree[$key]) == 0) unset($tree[$key]);
				if (is_object($input) && count($main[$key]) == 0) unset($main[$key]);
			} else {
				echo "storing $key in main\n";
				$main[$key] = $value;
			}
		}
	}
}

// Parse the JSON file and split the "class" tags from the rest.
$input = json_decode(file_get_contents(__DIR__."/driver.json"));
$tree = array();
$main = array();
separate($input, $tree, $main);

// Store the output in the repository.
$path = __DIR__."/repo/objects/1/1";
if (!file_exists($path)) {
	mkdir($path, 0777, true) or die("Unable to make directory $path.");
}
file_put_contents($path."/tree", json_encode($tree));
file_put_contents($path."/main", json_encode($main));
