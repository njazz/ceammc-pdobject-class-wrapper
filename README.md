This is a development/experimental repository / stub. 
Experimental feature for CEAMMC PureData library v0.7+
Check out the library itself:
http://github.com/uliss/pure-data


## Converter from C++ class to PureData objects. This is a stub.

![screenshot](demo.png?raw=true "screenshot")

To build:
- put C++ files in (to_wrap) folder (doesn't scan subfolders). 
- add sources to (to_include) and libraries to (to_link) folders.
- mkdir build && cd build && cmake .. && make

Python dependencies:
pycairo, cppheaderparser

Current limitations:
- Will not compile:
  * classes without copy/move constructors
  * unions in class or struct
  * variadic methods
  * constructors marked explicit
  * variadic functions
  * function-like macros
- Will skip:
  * template classes 
  * all operators

Todo list:
- doc gen for methods with no-default-constructor classes
- doc gen depending on function signatures
- filter custom attributes
- classes without copy/move constructors
- tests
- convert STL containers <-> lists 
- polymorphism

Tested in CEAMMC Pd 2018.03 (v0.5), CEAMMC Pd 2018.08 (v0.6)

Documentation is generated by pddoc:
http://github.com/uliss/pddoc

### Authors

* **Serge Poltavsky** - [uliss](https://github.com/uliss)
* **Alex Nadzharov** - [njazz](https://github.com/njazz)

### License
GPLv3


