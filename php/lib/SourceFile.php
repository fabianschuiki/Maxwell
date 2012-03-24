<?php

class SourceFile
{
	public $path;
	public $content;
	
	public function load($path = null)
	{
		if ($path) {
			$this->path = $path;
		}
		$this->content = file_get_contents($this->path);
	}
}
