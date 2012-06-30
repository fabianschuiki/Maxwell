<?php
namespace Source;

class File
{
	protected $path;
	protected $contents;
	
	public function __construct($path)
	{
		assert(is_string($path));
		$this->path = $path;
	}
	
	public function getPath()
	{
		return $this->path;
	}
	
	public function getContents()
	{
		if (!$this->contents) {
			$this->contents = file_get_contents($this->path);
			if (!$this->contents)
				IssueList::add('error', "Source file {$this->path} does not exist");
		}
		return $this->contents;
	}
}
