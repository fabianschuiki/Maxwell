<?php
namespace mwc;

class ImportedFile extends SourceFile
{
	public $let;
	
	public function load()
	{
		$intf = $this->interfacePath();
		if (!file_exists($intf)) Driver::error("interface '$intf' does not exist");
		$this->let = unserialize(file_get_contents($intf));
	}
}