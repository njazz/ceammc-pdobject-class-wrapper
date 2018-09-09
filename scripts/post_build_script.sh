#!/bin/sh

echo "[post-build script]"

echo "build dir $1"
echo "source dir $2"

lib_name=`cat $2/generated/library_name.txt`

echo "library name: $lib_name"

mv $1/wrapper_library.pd_darwin $1/$lib_name.pd_darwin
cp $1/$lib_name.pd_darwin $1/help/$lib_name.pd_darwin
