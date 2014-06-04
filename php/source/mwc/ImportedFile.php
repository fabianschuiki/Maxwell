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
		/*$let->bind();
		$let->reduce();*/
		$this->let = $let;
		assert($let instanceof \LET\Root);
		//file_put_contents($this->interfacePath().".imported.html", \Dump::let($let));
	}
	
	public function loadSpecs()
	{
		assert($this->let);
		$specs = $this->specsPath();
		$this->let->specializations = (file_exists($specs) ? unserialize(file_get_contents($specs)) : array());
	}
	
	///Writes all specialization requests in the root node to the specialization requests file.
	public function saveSpecs()
	{
		file_put_contents($this->specsPath(), serialize($this->let->specializations));
	}
}