<?php
namespace Store;
use Lexer\TokenList;
use Source\File;
use Coder;

class SyntaxStore
{
	protected $manager;
	protected $nodes;
	
	public function __construct(Manager $manager)
	{
		$this->manager = $manager;
		$this->nodes = array();
	}
	
	public function setSyntaxForFile(array $nodes, File $file)
	{
		$this->nodes[$file->getPath()] = $nodes;
	}
	
	public function getSyntaxForFile(File $file)
	{
		$nodes = @$this->nodes[$file->getPath()];
		if (!$nodes)
			throw new \exception("No syntax nodes exist for file '{$file->getPath()}'.");
		return $nodes;
	}
}