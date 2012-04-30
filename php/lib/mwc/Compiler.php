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
		global $issues;
		
		//Create the builtin CET if required.
		if (!static::$builtin) static::makeBuiltin();
		
		//Prepare the nodes for compilation, i.e. build some basic information structure.
		foreach ($nodeIDs as $id) {
			static::say("preparing $id");
			$input = new Entity($id, $this->driver->buildDir);
			$input->load();
			
			$cet = array();
			\CET\Node::make($input->mainNode(), $cet);
			
			file_put_contents($this->getCETPath($id), serialize($cet));
			$this->dumpCET($input, $cet, "preliminary");
		}
		
		//Compile each node to C.
		foreach ($nodeIDs as $id) {
			static::say("compiling $id");
			$input = new Entity($id, $this->driver->buildDir);
			$input->loadRecursively($externalEntities, $externalNodes);
			
			//Load the required CETs.
			$cet = static::$builtin;
			$ids = array_map(function($n) { return $n->id; }, $externalEntities);
			array_unshift($ids, $id);
			foreach ($ids as $i) {
				$cet_path = $this->getCETPath($i);
				if (!file_exists($cet_path)) static::error("missing CET file at $cet_path");
				$cet = array_merge($cet, unserialize(file_get_contents($cet_path)));
			}
			$this->dumpCET($input, $cet, "base");
			
			/*$input->mainNode()->bind();
			$input->mainNode()->reduce();
			if ($issues->dumpAndCheck()) return;*/
			
			//Process the main node.
			assert(isset($cet[$id]));
			$cet[$id]->process($input->mainNode(), $cet);
			$this->dumpCET($input, $cet);
			
			//Generate the C code.
			$code = new \C\Root;
			$cet[$id]->generateCode($code);
			$codePath = $input->debugPath();
			file_put_contents("$codePath.h", $code->getHeader());
			file_put_contents("$codePath.c", $code->getSource());
		}
	}
	
	public function dumpCET(Entity $input, array $cet, $suffix = null)
	{
		$str = "";
		foreach ($cet as $id => $node) $str .= "$id:  {$node->desc()}\n";
		$path = "{$input->debugPath()}.cet";
		if ($suffix) $path .= ".$suffix";
		$path .= ".txt";
		file_put_contents($path, $str);
	}
	
	public function getCETPath($id) { return "{$this->driver->buildDir}/compiled/$id.cet"; }
	
	static public function say($msg) { Driver::say("compiler: $msg"); }
	static public function debug($msg) { Driver::debug("compiler: $msg"); }
	static public function error($msg) { Driver::error("compiler: $msg"); }
	
	static private $builtin = null;
	static private function makeBuiltin()
	{
		$nodes = \LET\Scope::getBuiltinNodes();
		$builtin = array();
		foreach ($nodes as $id => $node) $builtin[$id] = \CET\Node::make($node, $builtin);
		static::$builtin = $builtin;
	}
}