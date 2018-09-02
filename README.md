This is a development/experimental repository / stub. 
Experimental feature for CEAMMC PureData library v0.7+
Check out the library itself:
http://github.com/uliss/pure-data


## Converter from C++ class to PureData objects. This is a stub.

![screenshot](demo.png?raw=true "screenshot")

To build:
- put C++ files in (to_wrap) folder (doesn't scan subfolders). 
- mkdir build && cd build && cmake .. && make

Current limitations:
- doesn't  convert classes without copy/move constructors
- skips template classes 
- skips all operators
- nested public classes with custom constructors don't compile

Todo list:
- destructors
- nested classes
- classes without copy/move constructors
- tests

Tested in CEAMMC Pd 2018.03 (v0.5)

### Authors

* **Serge Poltavsky** - [uliss](https://github.com/uliss)
* **Alex Nadzharov** - [njazz](https://github.com/njazz)

### License
GPLv3


