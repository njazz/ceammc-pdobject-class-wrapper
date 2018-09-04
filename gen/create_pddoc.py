#!/usr/bin/python
import sys
import os
import re

sys.path = ["../"] + sys.path

import CppHeaderParser3 as CppHeaderParser

# from subprocess import call

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
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")
    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="{2}">
        <title>{2}</title>
        <info>
            <par>{1}</par>
        </info>
        <meta>
            <authors>
                <author>Script</author>
            </authors>
            <description>{1}</description>
            <license>N/A</license>
            <library>wrapper_library </library>
            <category>{2}</category>
            <keywords>none</keywords>
            <since>1.0</since>
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
    # dbFile.write("{0} . .\n", objectType)
    # if len(fileName)>0:
    #     call(["pd_doc2pd",fileName, "--force"])

#----------

def write_pddoc_class_method_object(className,description,objectType, infoString):
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")
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
            <description> {2} is a method of {0}\n
            {1} </description>
            <license> N/A </license>
            <library> wrapper_library </library>
            <category>{0}</category>
            <keywords> none </keywords>
            <since> 1.0 </since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="any"> {3} </xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet> {3} </outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[

[B]
|
[{0}]
|  |
|  [ui.display]
|
|  [B] [1.0( [symbol test( [1 2 3(
|  |   |     |             |
[{2}                        ]
|
[ui.display]

[declare -lib ../wrapper_library]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(className,description,objectType, infoString))
    # dbFile.write("{0} . .\n", objectType)
    # if len(fileName)>0:
    #     call(["pd_doc2pd",fileName, "--force"])

# ---------------

def write_pddoc_static_method_object(className,description,objectType, infoString):
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")
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
            <description> {2} is a static \n
            method of {0}\n
            {1} </description>
            <license> N/A </license>
            <library> wrapper_library </library>
            <category>{0}</category>
            <keywords> none </keywords>
            <since> 1.0 </since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="any"> {3} </xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet> {3} </outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[


[B] [1.0( [symbol test( [1 2 3(
|   |     |             |
[{2}                        ]
|
[ui.display]

[declare -lib ../wrapper_library]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(className,description,objectType, infoString))
# ----------

def hasDefaultConstructor(cls):
    ret = False
    hasConstructor = False
    for m in cppHeader.classes[c]["methods"]["public"]:

        if m["constructor"]:
            hasConstructor = True
            methodType = [t["type"] for t in m["parameters"]]
            if methodType == "":
                ret = True
                continue
    #implicit
    if (not hasConstructor) and (not ret):
        ret = True
    return ret

# ---------------

dbFileName = "../build/doc/wrapper_library.db"
dbFile = open(dbFileName,"w+")

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
            if hasDefaultConstructor(cppHeader.classes[c]):
                write_pddoc_class_object(c, "no description", convert_name_n(c))
                dbFile.write("{0} . .\n".format(convert_name_n(c)))

            for m in cppHeader.classes[c]["methods"]["public"]:
                if m["template"] != False:
                    continue

                pdObjectName = convert_name_n(c)+"."+convert_name_n(m["name"])

                methodType = [t["type"] for t in m["parameters"]]
                methodReturn = m["rtnType"]

                methodInfoString = "("+" ".join(methodType)+")->"+methodReturn

                if m["static"] == True:
                    write_pddoc_static_method_object(convert_name_n(c), "no description", pdObjectName, methodInfoString)
                else:
                    write_pddoc_class_method_object(convert_name_n(c), "no description", pdObjectName, methodInfoString)

                dbFile.write("{0} . .\n".format(pdObjectName))
