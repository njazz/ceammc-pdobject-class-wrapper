**This is a development/experimental repository / stub.**

Experimental feature for CEAMMC PureData v0.7+
Check out the assembly/library itself:
http://github.com/uliss/pure-data


## Converter from C++ class to PureData objects.

![screenshot](demo.png?raw=true "screenshot")

**Requires CEAMMC Pd v0.6+**

To build in-place:
- clone this repository
- put C++ headers in (to_wrap) folder (doesn't scan subfolders).
- add sources to (to_build) and libraries to (to_link) folders.
- mkdir build && cd build && cmake .. && make

To create new library:
- create empty folder
- clone (this repository)/submodule/init_library.sh to your new folder
- chmod +x init_library.sh
- run ./init_library.sh
- edit library_info.cfg
- mkdir build && cd build && cmake .. && make


Python dependencies:  
pycairo, cppheaderparser, ply

Requires Boost 1.50+

---
##### Features

- Plain types are converted to Pd atoms (float, symbols). Other types are converted to CEAMMC DataAtom.
- Converts plain functions to single Pd objects. Receives list with appropriate data or bang if function has no arguments. Outputs list or doesn't output anything if function return type is void. Second object outlet outputs pointer to function as DataAtom - this is queried by 'func' message sent to the object.
- Converts classes with default constructors to Pd object that contains instance of that class and outputs it on bang. Outputs DataAtom.  
- Converts custom constructors of classes to "classname.new" objects. This object creates new instance of class when it receives appropriate list for initialization. Outputs DataAtom.  
- Converts class methods to single Pd objects. Objects derived from static class methods work as plain functions. Objects derived from non-static class methods require instance of class to be received as DataAtom.
- Converts lists <->vectors of strings/numbers
- Supports CEAMMC Set and Dict data types
- Can output functions, static and non-static methods as DataAtoms containing function pointer.

##### Current limitations

- Will not compile:
  * classes without copy/move constructors
  * unions in class or struct
  * variadic methods
  * constructors marked explicit
  * variadic functions
  * function-like macros
  * static functions with reference arguments
  * nested template (i.e. set<function<void(void)> >)

- Will skip:
  * template classes
  * all operators
  * enums

- Other issues:
  * static/plain function object that accepts pointer as argument crashes when it receives message
  * some types don't register as correct and output NULL DataAtom
  * objects report false "bad message format" error when function accepts vectors
  * messages with wrong arg count are truncated to last elements, this should be fixed


---
##### Todo list

- doc gen for methods with no-default-constructor classes
- doc gen depending on function signatures
- pointer types as function arguments
- filter custom attributes
- classes without copy/move constructors
- tests
- polymorphism
- enums
- properties with object flags (thread etc.)
- multiple inputs
- object flag for string/symbol output
- check DataTPtr pointers
- doc cleanup for plain functions  
- pass DOXYGEN comments to pddoc  
- class object containing all methods  
- local/global data objects  

Tested in CEAMMC Pd 2018.08 (v0.6)

Tp compile for CEAMMC Pd 2018.03 (v0.5):
* 'onAny' methods need to be rewritten with old headers.
* exclude new data type templates (in To/From CEAMMC .cpp files)

Documentation is generated by pddoc:
http://github.com/uliss/pddoc

---
### Authors

* **Serge Poltavsky** - [uliss](https://github.com/uliss)
* **Alex Nadzharov** - [njazz](https://github.com/njazz)

### License
GPLv3
