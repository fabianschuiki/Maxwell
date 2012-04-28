<?php
namespace mwc;

class Compiler
{
	public $driver;
	
	public function __construct(Driver $driver)
	{
		$this->driver = $driver;
	}
	
	public function compile(array $nodeIDs)
	{
		foreach ($nodeIDs as $id) {
			static::say("preparing $id");
			$input = new Entity($id, $this->driver->buildDir);
			$input->load($externalEntities, $externalNodes);
		}
	}
	
	static public function say($msg) { Driver::say("compiler: $msg"); }
}