#!/usr/bin/python
import sys
import os
import re

sys.path = ["../"] + sys.path

import CppHeaderParser3 as CppHeaderParser

from subprocess import call

# camelCase -> camel-case
def convert_name_h(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1-\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1-\2', s1).lower()

# camelCase -> camelcase
def convert_name_n(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1\2', s1).lower()

# ---------------
def write_pddoc_class_object(name,description,objectType):
    outputFile = open("../build/doc/"+name+".pddoc","w+")
    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="{2}">
        <title>{2}</title>
        <info>
            <par> {1} </par>
        </info>
        <meta>
            <authors>
                <author> Script </author>
            </authors>
            <description> {1} </description>
            <license> N/A </license>
            <library> wrapper_library </library>
            <category> all </category>
            <keywords> none </keywords>
            <since> 1.0 </since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="bang">Outputs {2}</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>Outputs {2}</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[

[B]
|
[{2}]
|
[ui.display]

[declare -lib ../wrapper_library]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(name,description,objectType))

# ---------------

for filename in os.listdir("../to_wrap/"):
    if filename.endswith(".hpp"):
        try:
            cppHeader = CppHeaderParser.CppHeader("../to_wrap/"+filename)
        except CppHeaderParser.CppParseError as e:
            print(e)
            sys.exit(1)

        for c in cppHeader.classes:
            className = c

            #stub:
            write_pddoc_class_object(c, "no description", convert_name_n(c))
