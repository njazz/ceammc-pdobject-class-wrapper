#!/bin/sh

mkdir ../build/doc
/usr/local/bin/python3 convert.py
/usr/local/bin/python3 create_pddoc.py
