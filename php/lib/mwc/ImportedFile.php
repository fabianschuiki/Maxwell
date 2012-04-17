<?php
namespace mwc;

class ImportedFile extends SourceFile
{
	public $let;
	
	public function load()
	{
		$intf = $this->interfacePath();
		if (!file_exists($intf)) Driver::error("interface '$intf' does not exist");
		$let = unserialize(file_get_contents($intf));
		$let->bind();
		$let->reduce();
		$this->let = $let;
		file_put_contents($this->interfacePath().".imported.html", \Dump::let($let));
	}
	
	///Writes all specialization requests in the root node to the specialization requests file.
	public function saveSpecs()
	{
		file_put_contents($this->specsPath(), serialize($this->let->specializations));
	}
}