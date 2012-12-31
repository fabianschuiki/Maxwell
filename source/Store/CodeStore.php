<?php
namespace Store;
use Source\File;

class CodeStore
{
	protected $manager;
	protected $dir;
	
	public function __construct(Manager $manager)
	{
		$this->manager = $manager;
		$this->dir = $manager->getDirectory()."/code";
	}
	
	public function persistCode($id, \Compiler\CodePair $code)
	{
		$path = $this->getPathToCode($id);
		static::ensureDirExists($path);
		
		file_put_contents("$path.h", $code->header);
		file_put_contents("$path.c", $code->source);
	}
	
	
	/*
	 * Paths
	 */
	
	private function getPathToCode($id)
	{
		return "{$this->dir}/$id";
	}
	
	static private function ensureDirExists($path)
	{
		$dir = dirname($path);
		if (!file_exists($dir)) @mkdir($dir, 0777, true);
	}
}