<?php
require_once __DIR__."/include.php";

$repo = new Repository("/tmp/maxwel-repo");
$repo->registerSource("frontend.mw");
$repo->registerSource("util/Console.mw");
$repo->registerSource("util/String.mw");
$repo->registerSource("util/File.mw");
$repo->flush();