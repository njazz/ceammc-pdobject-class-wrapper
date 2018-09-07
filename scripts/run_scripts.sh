#!/bin/sh

rm -R ../build/doc
mkdir ../build/doc
/usr/local/bin/python3 convert_headers.py
/usr/local/bin/python3 create_pddoc.py

cd ../build/
rm -R help
mkdir help
cd help

for file in ../doc/*
do
/usr/local/bin/pd_doc2pd "$file" --force --xlet-db ../doc/wrapper_library.db
done

/usr/local/bin/pd_makelibrary --library wrapper_library ../doc/* > ../doc/_wrapper_library.xml
cd ../doc/
/usr/local/bin/pd_lib2pd _wrapper_library.xml
cp wrapper_library-help.pd ../help/wrapper_library-help.pd

# fix
#echo "\n#X obj 300 15 declare -lib /../wrapper_library;" >> ../help/wrapper_library-help.pd
sed -i '' '2i\
#X declare -lib wrapper_library;\
#X obj 300 15 declare -lib wrapper_library;\
' ../help/wrapper_library-help.pd
