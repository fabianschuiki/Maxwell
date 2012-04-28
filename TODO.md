- Create a sandbox bind/reduce step right after parsing a file. This would reduce the complexity of the first `.intf` file generated, as local types are already resolved.
- Make `ConcreteType_Proxy` reduce itself appropriately at the beginning when some .intf or or .specs file is loaded.
- Remove `registerExternal` implementations.
- Remove debug candidates dumping in LET\Ident's bind.
- Keep track of what nodes generated specializations, and after specializing, only re-analyze new nodes and the ones that use the specializations.
- Merge the analysis and specialization stages of the Driver, so they happen at once. The loops are essentially just copies of one another, with slight changes.
- Make sure functions inside functions have their name prefixed with the enclosing function's name.


General Notes
=============

**Banker's Algorithm**: Check whether deadlocks may occur at all.