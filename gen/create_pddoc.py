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
            <description>Instance of {0} object.</description>
            <license>N/A</license>
            <library>wrapper_library</library>
            <category>{2}</category>
            <keywords>none</keywords>
            <since>1.0</since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="bang">Outputs DataAtom with {0} object.</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>Outputs DataAtom with {0} object.</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib wrapper_library]

[B]
|
[{2}]
|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(name,description,objectType))

#----------

def write_pddoc_class_method_object(className,description,objectType,methodType,methodReturn, cppClassName):
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")

    if len(methodType) == 0:
        methodType = "accepts bang"
    else:
        methodType = "accepts list: {0}".format(methodType)

    if len(methodReturn)==0:
        methodReturn = "no output"
    else:
        methodReturn = "list: {0}".format(methodReturn)

    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="{2}">
        <title>{2}</title>
        <info>
            <par>{1}</par>
        </info>
        <meta>
            <authors>
                <author> Script </author>
            </authors>
            <description>Method of {5}</description>
            <license> N/A </license>
            <library>wrapper_library</library>
            <category>{0}</category>
            <keywords> none </keywords>
            <since> 1.0 </since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="any">{3} </xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>{4} </outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib wrapper_library]

[B]
|
[{0}]
|  |
|  [ui.display @display_type 1]
|
|  [B] [1.0( [symbol test( [1 2 3(
|  |   |     |             |
[{2}                        ]
|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(className,description,objectType, methodType, methodReturn, cppClassName))

# ---------------

def write_pddoc_static_method_object(className,description,objectType, methodType,methodReturn, cppClassName):
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")
    if methodType == "[]":
        methodType = "accepts bang"
    else:
        methodType = "accepts list: {0}".format(methodType)

    if methodReturn =="[]":
        methodReturn = "no output"
    else:
        methodReturn = "list: {0}".format(methodReturn)

    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="{2}">
        <title>{2}</title>
        <info>
            <par>{1}</par>
        </info>
        <meta>
            <authors>
                <author> Script </author>
            </authors>
            <description>Static method of {5}</description>
            <license>N/A</license>
            <library>wrapper_library</library>
            <category>{0}</category>
            <keywords>none</keywords>
            <since>1.0</since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="any">{3} </xinfo>
                <xinfo on="symbol">'thread 1' sets the object to perform it's action in separate thread</xinfo>
                <xinfo on="symbol">'func' outputs object's function as DataAtom at second outlet</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>{4} </outlet>
            <outlet>Outputs DataAtom with {2} function.</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib wrapper_library]

[B] [1.0( [symbol test( [1 2 3(
|   |     |             |
[{2}                               ]
|
[ui.display @display_type 1]

[loadbang]
|
[thread 1(
|
|  [B] [1.0( [symbol test( [1 2 3(
|  |   |     |             |
[{2}                               ]
|
[ui.display @display_type 1]

[func(
|
[{2}]
^|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(className,description,objectType, methodType,methodReturn, cppClassName))
# ----------

def write_pddoc_class_custom_constructor_object(className,description,objectType, infoString):
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
                <author> Script </author>
            </authors>
            <description>Creates new instances of {0}</description>
            <license> N/A </license>
            <library>wrapper_library</library>
            <category>{0}</category>
            <keywords> none </keywords>
            <since> 1.0 </since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="bang">Outputs current instance of {0} </xinfo>
                <xinfo on="any">Creates new instance of {0} and outputs it</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>Outputs DataAtom with {0} object.</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib wrapper_library]

[B] [1.0( [symbol test( [1 2 3(
|   |     |             |
[{2}                        ]
|
[ui.display @display_type 1]

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
    if filename.endswith(".hpp") or filename.endswith(".h"):
        try:
            cppHeader = CppHeaderParser.CppHeader("../to_wrap/"+filename)
        except CppHeaderParser.CppParseError as e:
            print(e)
            sys.exit(1)

        for f in cppHeader.functions:
            m = f

            if m["template"] != False:
                continue

            pdObjectName = convert_name_n(m["name"])

            methodType = [t["type"] for t in m["parameters"]]
            methodReturn = m["rtnType"]

            methodInfoString = "("+" ".join(methodType)+")->"+methodReturn

            methodName = m["name"]

            write_pddoc_static_method_object("function", "", pdObjectName, methodType,methodReturn,"function")

            dbFile.write("{0} . ..\n".format(pdObjectName))


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

                lastClassName = className.split("::")[-1]
                customConstructor = False
                methodName = m["name"]

                if methodName == lastClassName:
                    #exclude default
                    if methodType != "":
                        customConstructor = True

                if customConstructor:
                    pdObjectName = convert_name_n(c)+".new"
                    write_pddoc_class_custom_constructor_object(convert_name_n(c), "", pdObjectName, methodInfoString)
                    dbFile.write("{0} . .\n".format(pdObjectName))
                    continue

                if m["static"] == True:
                    write_pddoc_static_method_object(convert_name_n(c), "", pdObjectName, methodType,methodReturn,c)
                else:
                    write_pddoc_class_method_object(convert_name_n(c), "", pdObjectName, methodType,methodReturn,c)

                dbFile.write("{0} . .\n".format(pdObjectName))
