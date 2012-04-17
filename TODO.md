- Create a sandbox bind/reduce step right after parsing a file. This would reduce the complexity of the first `.intf` file generated, as local types are already resolved.
- Rename `reduceToInterface` for all nodes except `Func` and `ConcreteType` to `reduceToBindable`, as the function's actual purpose is to return a new entity that has no resolved bindings.


General Notes
=============

**Banker's Algorithm**: Check whether deadlocks may occur at all.