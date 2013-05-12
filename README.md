Maxwell Programming Language
============================

At the moment, the compile process is undergoing major overhaul. Don't expect anything to work.

How To Dive In
--------------
At the moment most of the magic happens inside the `tests/` directory. The following commands if run from the root directory will get you going:

- `php tests/driver.init.php tests/driver.<something>.json` will parse the given JSON file and populate the local repository in `tests/repo` with entities.
- `php tests/driver.pretty.php` will pretty-print the contents of the repository to `tests/repo/pretty.mw`.
- `php tests/driver.stages.php` will perform one step in the compilation process by executing the next required processing step for one of the entities in the repository.

In order to reset one of the entities for repeat compilation, remove all the files except for `class`, `main` and `tree` in that entity's directory. The `stages` file is of particular interest, as it may be used to trigger certain compiler stages manually.