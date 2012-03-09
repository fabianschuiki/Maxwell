#!/usr/bin/php
<?php
require_once __DIR__.'/../lib/autoload.php';

$int    = new NamedType('int');
$float  = new NamedType('float');
$string = new NamedType('string');

$is = new TypeSet($int);
$fs = new TypeSet($float);
$ss = new TypeSet($string);

$ifs = new TypeSet;
$ifs->addNativeTypes(array('int', 'float'));

UnitTest::test($ifs->intersection($is), '{int}');
UnitTest::test($is->intersection($ifs), '{int}');
UnitTest::test($ifs->intersection($ss), '{}');
UnitTest::test($ss->intersection($ifs), '{}');