#!/usr/bin/php
<?php
require_once __DIR__.'/../lib/autoload.php';

function match(Type $a, Type $b, $desired)
{
	UnitTest::test("$a =? $b", $a->match($b), $desired);
}

//Types.
$int   = new NamedType('int');
$float = new NamedType('float');

//Type sets.
$int_or_float = new TypeSet($int, $float);


/**
 * TYPE SETS
 */

UnitTest::group("type sets");

//Simple.
$t1 = new TypeSet($int);
match($t1, $int, 'int');
match($int, $t1, 'int');

/**
 * TYPE VARIABLES
 */

//Simple.
$t1 = new TupleType;
$tva = new TypeVar('@a');
$t1->addField($tva);
$t1->addField($tva);

$t2 = new TupleType;
$t2->addField($int);
$t2->addField($int);

$t3 = new TupleType;
$t3->addField($int);
$t3->addField($float);

UnitTest::group("type variables");
match($t1, $t2, '(int, int)');
match($t1, $t3, 'nil');

//Multiple type variables.
$t1 = new TupleType;
$tva = new TypeVar('@a');
$t1->addField($tva);
$t1->addField($tva);
$t1->addField($int);

$t2 = new TupleType;
$tvb = new TypeVar('@b');
$t2->addField($int);
$t2->addField($tvb);
$t2->addField($tvb);

$t3 = new TupleType;
$tvb = new TypeVar('@b');
$t3->addField($float);
$t3->addField($tvb);
$t3->addField($tvb);

UnitTest::group("multiple type variables");
match($t1, $t2, '(int, int, int)');
match($t1, $t3, 'nil');

//Type sets.
$t1 = new TupleType;
$tva = new TypeVar('@a');
$t1->addField($tva);
$t1->addField($tva);

$t2 = new TupleType;
$t2->addField($int_or_float);
$t2->addField($int);

$t3 = new TupleType;
$t3->addField($int_or_float);
$t3->addField($float);

$t4 = new TupleType;
$t4->addField($int_or_float);
$t4->addField($int_or_float);

UnitTest::group("type sets and type variables");
match($t1, $t2, '(int, int)');
match($t1, $t3, '(float, float)');
match($t1, $t4, '({int, float}, {int, float})');


/**
 * FUNCTIONS
 */

//Combined with type variables.
$f1 = new FuncType;
$tva = new TypeVar('@a');
$f1->in->addField($tva);
$f1->in->addField($tva);
$f1->out->addField($tva);

$f2 = new FuncType;
$f2->in->addField($int);
$f2->in->addField($int);
$f2->out->addField($int);

$f3 = new FuncType;
$f3->in->addField($int);
$f3->in->addField($float);
$f3->out->addField($int);

$f4 = new FuncType;
$f4->in->addField($int);
$f4->in->addField($int);
$f4->out->addField($float);

$f5 = new FuncType;
$f5->in->addField($int);
$f5->in->addField($int_or_float);
$f5->out->addField($int);

$f6 = new FuncType;
$f6->in->addField(new TypeSet);
$f6->in->addField(new TypeSet);
$f6->out->addField($float);

$f7 = new FuncType;
$tva = new TypeVar('@a');
$f7->in->addField($tva, 'a');
$f7->in->addField($tva, 'b');
$f7->out->addField($tva, 'c');

$f8 = new FuncType;
$f8->in->addField($int, 'a');
$f8->in->addField($int, 'b');
$f8->out->addField($int, 'c');

UnitTest::group("functions");
match($f1, $f2, '(int, int)->(int)');
match($f1, $f3, 'nil');
match($f1, $f4, 'nil');
match($f1, $f5, '(int, int)->(int)');
match($f1, $f6, '(float, float)->(float)');
match($f2, $f8, '(a:int, b:int)->(c:int)');
match($f8, $f2, '(a:int, b:int)->(c:int)');
match($f2, $f7, '(a:int, b:int)->(c:int)');
match($f7, $f2, '(a:int, b:int)->(c:int)');
match($f6, $f7, '(a:float, b:float)->(c:float)');
match($f7, $f6, '(a:float, b:float)->(c:float)');
