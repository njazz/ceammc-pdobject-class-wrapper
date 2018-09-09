#!/bin/sh

echo build dir "$1"

#todo: receive from CMAKE
libname="$1/../generated/library_name.txt"
LIBRARY_NAME=`cat $libname` #"wrapper_library"

if [ $# -eq 0 ]
  then exit 1
fi

cfgoption="--config-file $2"
if [ "$2" = "" ]
  then
    cfgoption=""
fi

rm -R $1/doc
mkdir $1/doc
/usr/local/bin/python3 convert_headers.py
/usr/local/bin/python3 create_pddoc.py --build-dir $1 --library-name $LIBRARY_NAME $cfgoption

cd $1
rm -R help
mkdir help
cd help


for file in $1/doc/*
do
/usr/local/bin/pd_doc2pd "$file" --force --xlet-db $1/doc/$LIBRARY_NAME.db
done

/usr/local/bin/pd_makelibrary --library $LIBRARY_NAME $1/doc/* > $1/doc/_$LIBRARY_NAME.xml
cd $1/doc/
/usr/local/bin/pd_lib2pd _$LIBRARY_NAME.xml
cp $LIBRARY_NAME-help.pd $1/help/$LIBRARY_NAME-help.pd

# fix
sed -i '' '2i\
#X declare -lib $LIBRARY_NAME;\
#X obj 300 15 declare -lib $LIBRARY_NAME;\
' $1/help/$LIBRARY_NAME-help.pd
