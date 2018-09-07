#!/bin/sh

mkdir to_wrap
mkdir to_build
mkdir to_link

git init

mkdir wrapper
cd wrapper

git submodule add -b master https://github.com/njazz/ceammc-pdobject-class-wrapper.git
git submodule init

cd ..

cp wrapper/submodule/CMakeLists.txt CMakeLists.txt
