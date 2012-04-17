<?php
namespace mwc;

class SourceFile
{
	public $path;
	public $basePath;
	
	public function __construct($path, $buildDir)
	{
		assert(is_string($path));
		assert(is_string($buildDir));
		
		$this->path     = $path;
		$this->basePath = $buildDir."/".basename($this->path, ".mw");
	}
	
	public function interfacePath() { return $this->basePath.".intf"; }
	public function letPath()       { return $this->basePath.".let"; }
	public function specsPath()     { return $this->basePath.".specs"; }
}