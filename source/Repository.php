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
	protected $objects_unpersisted = array();
	protected $objects_modified = array();


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
		if ($this->objects_modified || $this->objects_unpersisted) $this->writeObjects();
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
			return $i;
		}
		return $this->sources[$path];
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

	/**
	 * Creates a new object of the class $class to be located inside source
	 * $sourceId and being a descendant of $rootId.
	 */
	public function makeObject($class, $sourceId, $rootId = null)
	{
		// Assemble the ID of this object.
		if (!$sourceId) {
			throw new \InvalidArgumentException("Source ID $sourceId is invalid.");
		}
		if ($rootId && strpos($rootId, $sourceId) !== 0) {
			throw new \InvalidArgumentException("Root ID $rootId is no descendant of source ID $sourceId.");
		}
		$baseId = ($rootId ? $rootId : $sourceId);
		for ($i = 1; ($id = "$baseId.$i") && isset($this->objects[$id]); $i++);

		// Create the new entity.
		$class_full = "\\Objects\\$class";
		if (!class_exists($class_full)) {
			throw new \InvalidArgumentException("Object class $class is unknown (i.e. PHP class $class_full does not exist). Maybe run entitygen again?");
		}
		$obj = new $class_full($this, $id);
		if (($rootId === null) != ($obj instanceof RepositoryRootObject)) {
			throw new \InvalidArgumentException("Object class $class cannot be a root object and have a parent root ID $rootId at the same time, or vice versa.");
		}
		$this->objects[$id] = $obj;
		if ($rootId === null) {
			$this->objects_unpersisted[] = $id;
		}
		return $obj;
	}

	/**
	 * Writes all modified objects to disk.
	 */
	private function writeObjects()
	{
		// Write the object class to disk where needed.
		foreach ($this->objects_unpersisted as $id) {
			$obj = @$this->objects[$id];
			if (!$obj) {
				throw new \RuntimeException("Object $id listed as to be persisted, but is not part of the repository.");
			}

			$file = $this->dir."/".$this->objects_dir."/".str_replace(".", "/", $id)."/class";
			if (file_exists($file)) {
				//throw new \RuntimeException("Trying to persist object $id for the first time, but file $file already exists.");
			}
			$this->mkdirIfNeeded(dirname($file));
			$class = preg_replace('/^(.*\\\)+/', "", get_class($obj));
			if (!file_put_contents($file, $class)) {
				throw new \RuntimeException("Unable to persist object $id class to $file.");
			}
		}
		$this->objects_unpersisted = array();

		// Write the modified fragments to disk.
		foreach ($this->objects_modified as $id) {
			$obj = @$this->objects[$id];
			if (!$obj) {
				throw new \RuntimeException("Object $id listed as modified, but is not part of the repository.");
			}

			// Iterate through the fragments of the entity that are modified and persist each.
			foreach ($obj->getFragmentNames() as $fragmentName) {
				$frag_dirty = $fragmentName."_dirty";
				if (!$obj->$frag_dirty) continue;
				$obj->$frag_dirty = false;

				// Assemble the output file name.
				$file = $this->dir."/".$this->objects_dir."/".str_replace(".", "/", $id)."/".$fragmentName;
				$this->mkdirIfNeeded(dirname($file));

				// Fetch the properties this fragment consists of.
				$properties = $obj->getFragment($fragmentName);

				// Generate the output for each property.
				$output = array();
				foreach ($properties as $property) {
					$output[$property["name"]] = "some ".$property["type"]." data";
				}

				// Store the output file.
				if (!file_put_contents($file, json_encode($output))) {
					throw new \RuntimeException("Unable to persist fragment $fragmentName of object $id to $file.");
				}
			}
		}
		$this->objects_modified = array();
	}

	public function notifyObjectFragmentDirty(RepositoryObject $object, $fragment)
	{
		$oid = $object->getId();
		if ($object instanceof RepositoryRootObject) {
			$rid = $oid;
		} else {
			if (!preg_match('/[^\.]*\.[^\.]/', $oid, $m)) {
				throw new \InvalidArgumentException("Object ID $oid does not contain a valid root portion.");
			}
			$rid = $m[1];
		}

		// Mark the corresponding root object as modified.
		if (!isset($this->objects[$rid])) {
			throw new \InvalidArgumentException("Unable to mark fragment $fragment of object ID $oid as modified since the root object ID $rid is not part of the repository.");
		}
		if (!in_array($rid, $this->objects_modified)) {
			$this->objects_modified[] = $rid;
		}
	}
}