<?php
namespace LET;

abstract class Type extends Node
{
	public function isConcrete() { return false; }
}