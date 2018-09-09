#!/bin/sh

echo CEAMMC Pd Library wrapper script

rm -Rf .git
rm -Rf wrapper

mkdir to_wrap
mkdir to_build
mkdir to_link
mkdir build

git init

git submodule add -b master https://github.com/njazz/ceammc-pdobject-class-wrapper.git wrapper
git submodule init

cp ./wrapper/submodule/CMakeLists.txt .
cp -n ./wrapper/submodule/library_info.cfg .

git add *
