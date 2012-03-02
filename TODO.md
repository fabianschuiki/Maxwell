- Create a Type class
  - name, fields
  - location of definition (AST node, other file, etc.)
  
- Create a Func class
  - name
  - patterns
  
- Create a FuncPattern class
  - input/output arguments
  - location of definition
  - function body

- Extend Scope class
  - Separate function array
  - Separate type array
  - Add function search which looks for FuncPattern instances for a given name
  - Add type search

- Implement some better version of late binding, where for each function call the Analyzer compiles a list of possible function patterns (including required implicit casts). The Analyzer should insert cast function calls as required.