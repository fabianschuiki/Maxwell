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
	protected $objects = array();
	protected $objects_dir = "objects";
	protected $objects_unpersisted = array();
	protected $objects_modified = array();

	// Logging options.
	public $debug = true;


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

	private function println($ln)
	{
		Log::println($ln, get_class());
	}

	private function getObjectDir($objectId)
	{
		return $this->dir."/".$this->objects_dir."/".str_replace(".", "/", $objectId);
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
			$id = $this->sources[$path];
			unset($this->sources[$path]);
			$this->sources_modified = true;
			$this->clearSource($id);
		} else {
			throw new InvalidArgumentException("Unable to unregister inexistent source $path.");
		}
	}

	/**
	 * Removes all entities associated with the given resource.
	 */
	public function clearSource($sourceId)
	{
		// Flush all changes to disk before attempting any modification.
		$this->flush();

		// Find all entities that belong to this source.
		$dir = $this->dir."/".$this->objects_dir."/".$sourceId;
		if (file_exists($dir)) {
			$d = opendir($dir);
			$ids = array();
			while ($subid = readdir($d)) {
				if ($subid[0] == ".") continue;
				$ids[] = $sourceId.".".$subid;
			}
			closedir($d);

			// Notify any dependencies of the removed entities.
			foreach ($ids as $id) {
				//$this->notifyObjectRemoved($id);
				if ($this->debug) $this->println("Removing object $id due to source clearing.");
			}

			// Remove the data stored for this source file.
			$result = shell_exec("rm -rf ".escapeshellarg($dir));
			if (strlen($result) > 0) {
				throw new \RuntimeException("Unable to remove objects for source ID $sourceId at $dir. $result.");
			}
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

		// Mark everything in the object as loaded.
		foreach ($obj->getFragmentNames() as $name) {
			$obj->{$name."_loaded"} = true;
		}
		return $obj;
	}

	/**
	 * Returns the object with the given ID or throws an exception if it does
	 * not exist.
	 */
	public function getObject($id)
	{
		// If the object has not been loaded yet, attempt to load it from disk.
		if (!isset($this->objects[$id])) {
			$file = $this->getObjectDir($id)."/class";
			if (!file_exists($file)) {
				throw new \InvalidArgumentException("Object ID $id does not exist at $file.");
			}

			// Load the class name and instantiate a new object.
			$class = file_get_contents($file);
			if (!$class) {
				throw new \RuntimeException("Unable to read class $file for object ID $id.");
			}
			$full_class = "\\Objects\\$class";
			$obj = new $full_class($this, $id);
			$this->objects[$id] = $obj;
			if ($this->debug) $this->println("Loaded object ID $id ($full_class)");
		}
		return $this->objects[$id];
	}

	/**
	 * Writes all modified objects to disk. This in fact iterates through the
	 * list of modified objects and writes all modified fragments to disk.
	 */
	private function writeObjects()
	{
		// All freshly created root objects need to be persisted to disk for the first time.
		foreach ($this->objects_unpersisted as $id)
		{
			// Retrieve the object.
			$obj = @$this->objects[$id];
			if (!$obj) {
				throw new \RuntimeException("Object $id listed as to be persisted, but is not part of the repository.");
			}

			// Make sure the filesystem is ready to accept the file.
			$file = $this->getObjectDir($id)."/class";
			if (file_exists($file)) {
				throw new \RuntimeException("Trying to persist object $id for the first time, but file $file already exists.");
			}
			$this->mkdirIfNeeded(dirname($file));

			// Write the class to the class file.
			$class = $obj->getClass();
			if (!file_put_contents($file, $class)) {
				throw new \RuntimeException("Unable to persist object $id class to $file.");
			}
		}
		$this->objects_unpersisted = array();

		// Write the modified fragments to disk.
		foreach ($this->objects_modified as $id)
		{
			// Retrieve the object.
			$obj = @$this->objects[$id];
			if (!$obj) {
				throw new \RuntimeException("Object $id listed as modified, but is not part of the repository.");
			}

			// Iterate through the fragments of the object that are modified and persist each.
			$stored = array();
			foreach ($obj->getFragmentNames() as $fragmentName)
			{
				// Do not persist fragments that are not dirty.
				$frag_dirty = $fragmentName."_dirty";
				if (!$obj->$frag_dirty) continue;
				$stored[] = $fragmentName;

				// Assemble the output file name and make sure the filesystem is ready to accept the file.
				$file = $this->getObjectDir($id)."/".$fragmentName.".out";
				$this->mkdirIfNeeded(dirname($file));

				// Generate the output for each property.
				$output = RepositoryObjectSerializer::serialize($obj, $fragmentName);

				// Store the output file.
				if (!file_put_contents($file, json_encode($output))) {
					throw new \RuntimeException("Unable to persist fragment $fragmentName of object $id to $file.");
				}

				// During debugging we also dump a more human-readable form of the output to disk.
				if ($this->debug) file_put_contents($file.".txt", print_r($output, true));
			}
			if ($this->debug) $this->println("Persisted ".implode(", ", $stored)." of object $id");
		}
		$this->objects_modified = array();
	}

	/**
	 * Called by RepositoryObject instances to notify the repository of changes
	 * to a given fragment.
	 */
	public function notifyObjectFragmentDirty($oid, $fragment)
	{
		echo "notifyObjectFragmentDirty($oid, $fragment)\n";

		// Add the object to the list of modified objects.
		if (!isset($this->objects[$oid])) {
			throw new \InvalidArgumentException("Unable to mark fragment $fragment of object ID $oid as modified since the object does not exist or is not loaded.");
		}
		if (!in_array($oid, $this->objects_modified)) {
			$this->objects_modified[] = $oid;
		}
	}

	/**
	 * Reads the requested fragment file for the given object from the disk and
	 * loads its contents into the object.
	 */
	public function loadObjectFragment($oid, $fragment)
	{
		echo "loadObjectFragment($oid, $fragment)\n";
		$prop_dirty  = $fragment."_dirty";
		$prop_loaded = $fragment."_loaded";

		// Fetch the object with this ID.
		if (!isset($this->objects[$oid])) {
			throw new \InvalidArgumentException("Object ID $oid does not exist or is not loaded.");
		}
		$object = $this->objects[$oid];

		// Make sure nothing is loaded yet or the loaded data is not dirty.
		if ($object->$prop_dirty) {
			throw new \RuntimeException("Asked to load fragment $fragment of object ID $oid, but the loaded data is marked as dirty.");
		}
		if ($object->$prop_loaded) {
			throw new \RuntimeException("Asked to load fragment $fragment of object ID $oid which is already loaded.");
		}
		$object->$prop_loaded = true;

		// Attempt to load the fragment information from the fragment file.
		$file = $this->getObjectDir($oid)."/".$fragment;
		if (file_exists($file)) {
			if ($this->debug) $this->println("Loading object ID {$oid} fragment $fragment");
			$data = file_get_contents($file);
			if ($data === false) {
				throw new \RuntimeException("Unable to read file $file.");
			}
			$input = json_decode($data);
			if ($input === false) {
				throw new \RuntimeException("Unable to parse JSON file $file. JSON error ".json_last_error().".");
			}

			// Parse the loaded JSON file.
			RepositoryObjectSerializer::unserialize($object, $fragment, $input);
		}
	}
}