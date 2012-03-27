<?php
namespace LET;

abstract class Type extends Node
{
	public function isSpecific() { return false; }
}