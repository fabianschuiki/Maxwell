<?php
namespace Driver;
use Store\Manager;
use IssueList;
use Source\File;

class Frontend
{
	protected $files;
	protected $importMap;
	
	public function __construct()
	{
		$this->files = array();
		$this->importMap = array();
	}
	
	public function addFile($f) { $this->files[] = $f; }
	public function addFiles(array $f) { $this->files = array_merge($this->files, $f); }
	public function getFiles() { return $this->files; }
	
	protected function tokenize(File $file)
	{
		$manager = Manager::get();
		
		$lexer = new \Lexer\Lexer($file);
		$lexer->run();
		if (IssueList::get()->isFatal()) return false;
		$manager->getTokenStore()->setTokensForFile($lexer->getTokens(), $file);
		
		return true;
	}
	
	protected function parse(File $file)
	{
		$manager = Manager::get();
		$issues = IssueList::get();
		
		$parser = new \Parser\Parser($manager->getTokenStore()->getTokensForFile($file));
		$parser->run();
		if ($issues->isFatal()) return false;
		$manager->getSyntaxStore()->setSyntaxForFile($parser->getNodes(), $file);
		
		//Resolve file imports.
		$dir = dirname($file->getPath());
		$imports = array();
		foreach ($parser->getNodes() as $node) {
			if (!$node instanceof \AST\Stmt\Import) continue;
			foreach ($node->getNames() as $nameToken) {
				$name = $nameToken->getText();
				$path = "$dir/$name";
				if (!preg_match('/\.mw$/', $path)) $path .= ".mw";
				
				if (!file_exists($path)) {
					IssueList::add('error', "Imported file '$name' not found.", $nameToken);
					continue;
				}
				array_push($this->files, $path);
				$imports[] = $path;
			}
		}
		$this->importMap[$file->getPath()] = $imports;
		
		return !$issues->isFatal();
	}
	
	protected function entitialize(File $file)
	{
		$manager = Manager::get();
		$manager->getEntityStore()->clearEntitiesInFile($file);
		
		$entitializer = new \Entitializer($manager->getSyntaxStore()->getSyntaxForFile($file), $file);
		$entitializer->run();
		if (IssueList::get()->isFatal()) return false;
		
		$es = $manager->getEntityStore();
		foreach ($entitializer->getEntities() as $e) {
			$e->pushID();
			$e->initScope(null);
			$e->popID();
			$es->setEntity($e);
		}
		
		return true;
	}
	
	public function run()
	{
		$manager = Manager::get();
		
		$issues = new IssueList;
		$issues->push();
		
		//Tokenize and parse the files.
		$processedFiles = array();
		$processedPaths = array();
		while (count($this->files)) {
			$path = array_shift($this->files);
			if (in_array($path, $processedPaths)) continue;
			$processedPaths[] = $path;
			
			$file = $manager->getSourceFileAtPath($path);
			if (!$this->tokenize($file)) continue;
			if (!$this->parse($file)) continue;
			$processedFiles[] = $file;
		}
		
		//Entitialize all processed files.
		foreach ($processedFiles as $file) {
			$this->entitialize($file);
		}
		
		//Resolve known entities..
		$es = $manager->getEntityStore();
		foreach ($processedFiles as $file) {
			$imported = array();
			foreach ($this->importMap[$file->getPath()] as $import) {
				foreach ($es->getEntityIDsInFile($import) as $id) {
					$imported[] = $es->getEntity($id);
				}
			}
			foreach ($es->getEntityIDsInFile($file->getPath()) as $id) {
				$e = $es->getEntity($id);
				$known = array_merge($e->getSiblingEntities(), $imported);
				$e->setKnownEntities($known);
				$es->persistEntity($id);
			}
		}
		
		$issues->pop();
		$issues->report();
	}
}