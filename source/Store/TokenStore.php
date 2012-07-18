<?php
namespace Store;
use Lexer\TokenList;
use Source\File;
use Coder;

class TokenStore
{
	protected $manager;
	protected $dir;
	protected $tokens;
	
	public function __construct(Manager $manager)
	{
		$this->manager = $manager;
		$this->dir = $manager->getDirectory()."/tokens";
		$this->tokens = array();
	}
	
	public function allocateId()
	{
		return $this->manager->allocateId();
	}
	
	public function setTokensForFile(TokenList $tokens, File $file)
	{
		$this->tokens[$file->getPath()] = $tokens;
		
		//Transform the tokens into an encodable representation.
		$root = new Coder\Element("tokens");
		$this->serializeTokens($tokens, $root);
		
		//Persist the tokens.
		$path = $this->getPathToTokens($file);
		$dir = dirname($path);
		if (!file_exists($dir))	mkdir(dirname($dir), 0777, true);
		
		$xml = new Coder\XMLCoder;
		$xml->encodeToFile($root, $path);
	}
	
	public function getTokensForFile(File $file)
	{
		$tokens = @$this->tokens[$file->getPath()];
		if (!$tokens) trigger_error("Token decoding not implemented yet", E_USER_ERROR);
		return $tokens;
	}
	
	public function isFileOutdated(File $file)
	{
		$path = $this->getPathToTokens($file);
		if (!file_exists($path)) return true;
		return filemtime($path) < filemtime($file->getPath());
	}
	
	
	
	private function getPathToTokens(File $file)
	{
		$name = preg_replace('/\.mw$/i', '.tokens', $file->getPath());
		return "{$this->dir}/$name";
	}
	
	private function serializeTokens(TokenList $tokens, Coder\Element $parent)
	{
		foreach ($tokens->getTokens() as $t) {
			$e = $parent->makeElement($t->getType());
			$e->setAttribute('id', $t->getID());
			$e->setAttribute('text', $t->getText());
			$e->setAttribute('range', $t->getRange()->toString());
			if ($t->is('group'))
				$this->serializeTokens($t->getTokens(), $e);
		}
	}
}