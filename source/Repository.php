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

	// Logging facilities.
	static public $verbosity = 1;
	private function println($verbosity, $ln, $info = null)
	{
		if (static::$verbosity > $verbosity)
			Log::println($ln, get_class(), $info);
	}

	/// Serializer used in this repo.
	protected $serializer;

	/// Repository for builtin objects.
	protected $builtin;

	// Object IDs the individual stages depend upon.
	protected $dependencies = array();
	protected $dependencies_modified = array();

	// State of the stages of the individual objects.
	protected $objectStageStates = array();
	protected $objectStageStates_modified = array();

	// List of local names per source.
	protected $localNames = array();
	protected $localNames_modified = array(); // unused as of now


	/// Create a new repository at the location $dir.
	public function __construct($dir)
	{
		$this->dir = $dir;
		$this->mkdirIfNeeded($dir);
		$this->serializer = new RepositoryObjectSerializer($this);
		$this->builtin = new BuiltinObjects($this);
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
		if ($this->dependencies_modified) $this->writeDependencies();
		if ($this->objectStageStates_modified) $this->writeObjectStageStates();
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
				$this->println(0, "Removing object $id due to source clearing.", $sourceId);
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
		// Redirect builtin object requests.
		if (preg_match('/^0\./', $id)) {
			return $this->builtin->getObject($id);
		}

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
			$this->println(0, "Loaded object ID $id ($full_class)");
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
				$file = $this->getObjectDir($id)."/".$fragmentName;
				if ($fragmentName == "tree" || $fragmentName == "main") $file .= ".out"; //DEBUG
				$this->mkdirIfNeeded(dirname($file));

				// Generate the output for each property.
				$output = $this->serializer->serialize($obj, $fragmentName);

				// Store the output file.
				if (!file_put_contents($file, json_encode($output))) {
					throw new \RuntimeException("Unable to persist fragment $fragmentName of object $id to $file.");
				}

				// During debugging we also dump a more human-readable form of the output to disk.
				if (static::$verbosity > 0) file_put_contents($file.".txt", print_r($output, true));
			}
			$this->println(0, "Persisted ".implode(", ", $stored), $id);
		}
		$this->objects_modified = array();
	}

	/**
	 * Called by RepositoryObject instances to notify the repository of changes
	 * to a given fragment.
	 */
	public function notifyObjectFragmentDirty($oid, $fragment)
	{
		$this->println(1, "Notify fragment $fragment dirty", $oid);

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
		$this->println(1, "Load fragment $fragment", $oid);
		$prop_dirty  = $fragment."_dirty";
		$prop_loaded = $fragment."_loaded";

		// Fetch the object with this ID.
		if (!isset($this->objects[$oid])) {
			throw new \InvalidArgumentException("Object ID $oid does not exist or is not loaded.");
		}
		$object = $this->objects[$oid];

		// Check whether the object supports this fragment.
		if (!isset($object->$prop_loaded)) {
			throw new \RuntimeException("Object $oid does not support fragment '$fragment'. Maybe one of its children contains this fragment and the root wrongly does not?");
		}

		// Make sure nothing is loaded yet or the loaded data is not dirty.
		if ($object->$prop_dirty) {
			throw new \RuntimeException("Asked to load fragment $fragment of object ID $oid, but the loaded data is marked as dirty.");
		}
		if ($object->$prop_loaded) {
			throw new \RuntimeException("Asked to load fragment $fragment of object ID $oid which is already loaded.");
		}

		// Mark the fragment as loaded.
		$this->recursivelyMarkFragmentLoaded($object, $fragment);

		// Attempt to load the fragment information from the fragment file.
		$file = $this->getObjectDir($oid)."/".$fragment;
		if (file_exists($file)) {
			$data = file_get_contents($file);
			if ($data === false) {
				throw new \RuntimeException("Unable to read file $file.");
			}
			$input = json_decode($data);
			if ($input === false) {
				throw new \RuntimeException("Unable to parse JSON file $file. JSON error ".json_last_error().".");
			}

			// Parse the loaded JSON file.
			$this->serializer->unserialize($object, $fragment, $input);
		}
	}

	/**
	 * Marks the object and object's children as having loaded the fragment.
	 */
	private function recursivelyMarkFragmentLoaded(RepositoryObject $object, $fragment)
	{
		if (isset($object->{$fragment."_loaded"})) {
			$object->{$fragment."_loaded"} = true;
		}
		if ($fragment != "tree") {
			foreach ($object->getChildren() as $child) {
				$this->recursivelyMarkFragmentLoaded($child, $fragment);
			}
		}
	}

	/**
	 * Returns a list with id-name pairs of external objects the object given
	 * by $objectId knows about. This also contains the builtin objects.
	 */
	public function getImportedNamesForObject($objectId)
	{
		$a = array();
		$a = array_merge($a, $this->getLocalNamesForObject($objectId));
		$a = array_merge($a, $this->builtin->getObjectNames());
		return $a;
	}

	/**
	 * Returns a list of local names and IDs, i.e. the list of locally declared
	 * functions and types for the given object's source.
	 */
	public function getLocalNamesForObject($objectId)
	{
		if (!preg_match('/^(\d*)\./', $objectId, $m)) {
			throw new \InvalidArgumentException("Object ID $objectId has no valid source segment.");
		}
		return $this->getLocalNames($m[1]);
	}

	/**
	 * Returns the given builtin type or throws an exception if it does not
	 * exist.
	 */
	public function getBuiltinType($name)
	{
		foreach ($this->builtin->getObjectNames() as $id => $n) {
			if ($n === $name)
				return $this->builtin->getObject($id);
		}
		throw new \InvalidArgumentException("No internal object named '$name' exists.");
	}

	/**
	 * Removes all dependencies for this stage.
	 */
	public function resetStageDependencies($stage, $objectId)
	{
		$this->println(2, "Resetting dependencies of stage $stage", $objectId);
		if (!isset($this->dependencies[$objectId])) {
			$this->readDependencies($objectId);
		}
		if (isset($this->dependencies[$objectId][$stage])) {
			unset($this->dependencies[$objectId][$stage]);
			if (!in_array($objectId, $this->dependencies_modified)) {
				$this->dependencies_modified[] = $objectId;
			}
		}
	}

	/**
	 * Marks the given object ID at the given stage depending on the given
	 * other object.
	 */
	public function addStageDependency($stage, $objectId, $dependsOnId)
	{
		if (!isset($this->dependencies[$objectId])) {
			$this->readDependencies($objectId);
		}
		if (!isset($this->dependencies[$objectId][$stage]) || !in_array($dependsOnId, $this->dependencies[$objectId][$stage])) {
			$this->dependencies[$objectId][$stage][] = $dependsOnId;
			$this->println(3, "Stage $stage depends on $dependsOnId", $objectId);
			if (!in_array($objectId, $this->dependencies_modified)) {
				$this->dependencies_modified[] = $objectId;
			}
		}
	}

	/**
	 * Writes the dependencies to disk for all objects listed under
	 * dependencies_modified.
	 */
	private function writeDependencies()
	{
		foreach ($this->dependencies_modified as $objectId) {
			if (!isset($this->dependencies[$objectId])) {
				throw new \RuntimeException("Dependencies for object ID $objectId marked as modified, but the dependencies themselves don't exist.");
			}
			$this->println(1, "Write dependencies", $objectId);
			$deps = $this->dependencies[$objectId];
			$path = $this->getObjectDir($objectId)."/dependencies";
			if (!file_put_contents($path, json_encode($deps))) {
				throw new \RuntimeException("Unable to write dependencies of object ID $objectId to $path.");
			}
			if (static::$verbosity > 0) {
				file_put_contents($path.".txt", print_r($deps, true));
			}
		}
		$this->dependencies_modified = array();
	}

	/**
	 * Reads the dependencies for the given object ID and stores them in the
	 * dependencies tree.
	 */
	private function readDependencies($objectId)
	{
		if (in_array($objectId, $this->dependencies_modified)) {
			throw new \RuntimeException("Loading dependencies of object ID $objectId which are marked as modified.");
		}
		$path = $this->getObjectDir($objectId)."/dependencies";
		$this->println(1, "Read dependencies", $objectId);

		if (file_exists($path)) {
			$source = file_get_contents($path);
			if ($source === false) {
				throw new \RuntimeException("Unable to read dependencies file $path.");
			}
			$deps = json_decode($source, true);
			if ($deps === null) {
				throw new \RuntimeException("Unable to parse dependencies in file $path. JSON error ".json_last_error().".");
			}
			$this->dependencies[$objectId] = $deps;
		}
	}

	/**
	 * Called by objects in the repository whenever an object changes. This
	 * information is used to invalidate certain object stages.
	 */
	public function notifyObjectDirty($objectId, $path)
	{
		$this->println(3, "Modified $path", $objectId);

		// Look for such a dependency.
		foreach ($this->dependencies as $oid => $deps) {
			foreach ($deps as $stage => $ids) {
				if (in_array($objectId.".".$path, $ids)) {
					$this->println(2, "- Invalidates $oid stage $stage", $objectId);
					$this->setObjectStageState($oid, $stage, false);
				}
			}
		}
	}

	/**
	 * Writes all modified stage states to disk.
	 */
	private function writeObjectStageStates()
	{
		foreach ($this->objectStageStates_modified as $objectId) {
			if (!isset($this->objectStageStates[$objectId])) {
				throw new \RuntimeException("Stage states for object ID $objectId marked as modified, but the stage states themselves don't exist.");
			}
			$this->println(1, "Write stage states", $objectId);
			$states = $this->objectStageStates[$objectId];
			$path = $this->getObjectDir($objectId)."/stages";
			if (!file_put_contents($path, json_encode($states))) {
				throw new \RuntimeException("Unable to write stage states of object ID $objectId to $path.");
			}
			if (static::$verbosity > 0) {
				file_put_contents($path.".txt", print_r($states, true));
			}
		}
	}

	/**
	 * Reads the stage states for the given object from disk. You should not
	 * have to call this function directly as it is called loaded through the
	 * accessors.
	 */
	private function readObjectStageStates($objectId)
	{
		if (in_array($objectId, $this->objectStageStates_modified)) {
			throw new \RuntimeException("Loading stage states of object ID $objectId which are marked as modified.");
		}
		$path = $this->getObjectDir($objectId)."/stages";
		$this->println(1, "Read stage states", $objectId);

		if (file_exists($path)) {
			$source = file_get_contents($path);
			if ($source === false) {
				throw new \RuntimeException("Unable to read stage states file $path.");
			}
			$states = json_decode($source, true);
			if ($states === null) {
				throw new \RuntimeException("Unable to parse stage states in file $path. JSON error ".json_last_error().".");
			}
			$this->objectStageStates[$objectId] = $states;
		}
	}

	/**
	 * Returns the state of the given stage for the given object, i.e. true if
	 * the stage has been executed and is valid, or false if it either has not
	 * been executed yet or is invalid due to changes to dependencies.
	 */
	public function getObjectStageState($objectId, $stage)
	{
		if (!isset($this->objectStageStates[$objectId]))
			$this->readObjectStageStates($objectId);

		if (isset($this->objectStageStates[$objectId][$stage])) {
			return $this->objectStageStates[$objectId][$stage];
		} else {
			return false;
		}
	}

	/**
	 * Sets the state of the given stage for the given object. True means the
	 * stage is valid, false means the stage needs to be run again.
	 */
	public function setObjectStageState($objectId, $stage, $state)
	{
		$this->objectStageStates[$objectId][$stage] = $state;
		if (!in_array($objectId, $this->objectStageStates_modified)) {
			$this->objectStageStates_modified[] = $objectId;
		}
	}

	/**
	 * Returns a list of locally names declared locally in the given source.
	 */
	public function getLocalNames($sourceId)
	{
		if (!isset($this->localNames[$sourceId])) {
			$this->readLocalNames($sourceId);
		}
		return $this->localNames[$sourceId];
	}

	/**
	 * Returns the path to the local names store for the given source ID.
	 */
	private function getLocalNamesPath($sourceId)
	{
		return $path = $this->dir."/".$this->objects_dir."/".$sourceId."/names-local";
	}

	/**
	 * Reads the list of local names for the given source ID.
	 */
	private function readLocalNames($sourceId)
	{
		if (in_array($sourceId, $this->localNames_modified)) {
			throw new \RuntimeException("Loading local names of source ID $sourceId which are marked as modified.");
		}

		$path = $this->getLocalNamesPath($sourceId);
		$names = array();
		if (file_exists($path)) {
			$source = file_get_contents($path);
			if ($source === false) {
				throw new \RuntimeException("Unable to read local names file $path.");
			}
			$names = json_decode($source, true);
			if ($names === null) {
				throw new \RuntimeException("Unable to parse local names in file $path. JSON error ".json_last_error().".");
			}
		}
		$this->localNames[$sourceId] = $names;
	}
}