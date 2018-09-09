#!/bin/sh

echo build dir "$1"

lib_name=`cat $1/../generated/library_name.txt`
mv $1/wrapper_library.pd_darwin $1/$lib_name.pd_darwin
cp $1/$lib_name.pd_darwin $1/help/$lib_name.pd_darwin
