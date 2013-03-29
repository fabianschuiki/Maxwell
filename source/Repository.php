<?php
/* Copyright © 2013 Fabian Schuiki */

/**
 * @brief Maintains intermediate build files.
 *
 * The repository represents a storage facility used to persist information
 * during compilation.
 */
class Repository
{
	/// Path to the repository directory.
	protected $dir;

	/// Registered source files.
	protected $sources;
	protected $sources_db = "sources";
	protected $sources_modified = false;

	/// Registered objects.
	protected $objects;
	protected $objects_dir = "objects";


	/// Create a new repository at the location $dir.
	public function __construct($dir)
	{
		$this->dir = $dir;
		$this->mkdirIfNeeded($dir);
	}

	/// Creates the directory $dir if it does't exist.
	private function mkdirIfNeeded($dir)
	{
		if (!file_exists($dir)) {
			if (!mkdir($dir, 0777, true)) {
				throw new RuntimeException("Unable to create directory $dir.");
			}
		}
	}

	/**
	 * Flushes all changes to the repository to the disk. Changes are not
	 * persistent before a call to flush().
	 */
	public function flush()
	{
		if ($this->sources_modified) $this->writeSources();
	}

	/**
	 * Registers the source file $path in the repository, assigning it an ID if
	 * it does not have one yet.
	 */
	public function registerSource($path)
	{
		if (!$this->sources)
			$this->readSources();
		if (!isset($this->sources[$path])) {
			for ($i = 1; in_array($i, $this->sources); $i++);
			$this->sources[$path] = $i;
			$this->sources_modified = true;
		}
	}

	/**
	 * Unregisters the source file $path, removing all traces of its existence
	 * from the repository.
	 */
	public function unregisterSource($path)
	{
		if (!$this->sources)
			$this->readSources();
		if (isset($this->sources[$path])) {
			unset($this->sources[$path]);
			$this->sources_modified = true;
			// TODO: Remove all remnants of this source from the repository.
		} else {
			throw new InvalidArgumentException("Unable to unregister inexistent source $path.");
		}
	}

	/**
	 * Reads the registered source files from the repository. If no information
	 * is stored on disk simply initializes an empty list of source files.
	 */
	private function readSources()
	{
		// Make sure we don't accidentally override modified sources.
		if ($this->sources_modified) {
			throw new LogicException("Reading sources from disk would overwrite modified sources in memory.");
		}

		// Load the sources.
		$db = $this->dir."/".$this->sources_db;
		if (file_exists($db)) {
			$sources = array();
			$file = file($db, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
			if ($file === false)
				throw new RuntimeException("Unable to read file $db.");
			foreach ($file as $line) {
				if (!preg_match('/\s*(\d+)\s+(.*)/s', $line, $m))
					throw new InvalidArgumentException("Invalid line '$line' in $db.");
				$sources[$m[2]] = $m[1];
			}
			$this->sources = $sources;
		} else {
			$this->sources = array();
		}
	}

	/**
	 * Persists the registered source files to the repository.
	 */
	private function writeSources()
	{
		$this->sources_modified = false;
		$db = $this->dir."/".$this->sources_db;
		$f = fopen($db, "w");
		if ($f === false)
			throw new RuntimeException("Unable to open file $db for writing.");
		foreach ($this->sources as $name => $id) {
			fprintf($f, "%d  %s\n", $id, $name);
		}
		fclose($f);
	}
}