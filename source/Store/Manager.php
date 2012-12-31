<?php
namespace Store;

class Manager
{
	//Stacking mechanism
	static $stack = array();
	
	static public function get()
	{
		assert(count(static::$stack) > 0);
		return static::$stack[count(static::$stack)-1];
	}
	
	public function push()
	{
		array_push(static::$stack, $this);
	}
	
	public function pop()
	{
		$popped = array_pop(static::$stack);
		assert($popped === $this);
	}
	
	
	//Instance
	protected $dir;
	protected $nextId;
	protected $sourceFiles;
	protected $tokenStore;
	protected $syntaxStore;
	protected $entityStore;
	protected $codeStore;
	
	public function __construct($dir)
	{
		$this->dir = rtrim($dir, '/');
		$this->sourceFiles = array();
		$this->nextID = null;
	}
	
	public function getDirectory() { return $this->dir; }
	
	/** Returns the path to the file storing the autogenerated id. */
	public function getIdStorePath()
	{
		return $this->dir."/id";
	}
	
	/** Returns the next unused id. */
	public function allocateId()
	{
		$path = $this->getIdStorePath();
		if (!$this->nextId && file_exists($path))
			$this->nextId = file_get_contents($path);
		if (!$this->nextId)
			$this->nextId = 1;
		$i = $this->nextId++;
		$dir = dirname($path);
		if (!file_exists($dir))	mkdir($dir, 0777, true);
		file_put_contents($path, $this->nextId);
		return $i;
	}
	
	public function getSourceFileAtPath($path)
	{
		$f = @$this->sourceFiles[$path];
		if (!$f) {
			$f = new \Source\File($path);
			$this->sourceFiles[$path] = $f;
		}
		return $f;
	}
	
	public function getTokenStore()
	{
		if (!$this->tokenStore)
			$this->tokenStore = new TokenStore($this);
		return $this->tokenStore;
	}
	
	public function getSyntaxStore()
	{
		if (!$this->syntaxStore)
			$this->syntaxStore = new SyntaxStore($this);
		return $this->syntaxStore;
	}
	
	public function getEntityStore()
	{
		if (!$this->entityStore)
			$this->entityStore = new EntityStore($this);
		return $this->entityStore;
	}
	
	public function getCodeStore()
	{
		if (!$this->codeStore)
			$this->codeStore = new CodeStore($this);
		return $this->codeStore;
	}
}