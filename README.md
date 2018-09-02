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

Current limitations:
- Will not compile:
  * classes without copy/move constructors
  * unions in class or struct
  * variadic functions
  * constructors marked explicit
- Will skip:
  * template classes 
  * all operators

Todo list:
- destructors
- filter custom attributes
- classes without copy/move constructors
- tests
- convert STL containers <-> lists 
- polymorphism

Tested in CEAMMC Pd 2018.03 (v0.5), CEAMMC Pd 2018.08 (v0.6)

### Authors

* **Serge Poltavsky** - [uliss](https://github.com/uliss)
* **Alex Nadzharov** - [njazz](https://github.com/njazz)

### License
GPLv3


