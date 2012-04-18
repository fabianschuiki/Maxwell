- Create a sandbox bind/reduce step right after parsing a file. This would reduce the complexity of the first `.intf` file generated, as local types are already resolved.
- Make `ConcreteType_Proxy` reduce itself appropriately at the beginning when some .intf or or .specs file is loaded.


General Notes
=============

**Banker's Algorithm**: Check whether deadlocks may occur at all.