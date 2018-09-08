#!/usr/bin/python
import sys
import os
import re

#TODO: template XML files

import common_functions as gen

# ---------------

def classObject(name,description,objectType):
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")
    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="{CLASSNAME_PD}">
        <title>{CLASSNAME_PD}</title>
        <info>
            <par>{DESCR}</par>
        </info>
        <meta>
            <authors>
                <author>Script</author>
            </authors>
            <description>Instance of {CLASSNAME_CXX} object.</description>
            <license>N/A</license>
            <library>wrapper_library</library>
            <category>{CLASSNAME_PD}</category>
            <keywords>none</keywords>
            <since>1.0</since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="bang">Outputs DataAtom with {CLASSNAME_CXX} object.</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>Outputs DataAtom with {CLASSNAME_CXX} object.</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib wrapper_library]

[B]
|
[{CLASSNAME_PD}]
|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(CLASSNAME_CXX = name, DESCR = description, CLASSNAME_PD = objectType))

#----------

def classMethodObject(className,description,objectType,methodType,methodReturn, cppClassName):
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")

    methodTypeStr = ",".join(methodType)
    methodTypeStr.replace("<","(")
    methodTypeStr.replace(">",")")
    methodReturn.replace("<","(")
    methodReturn.replace(">",")")

    if methodType == "[]":
        methodTypeStr = "accepts bang"
    else:
        methodTypeStr = "accepts list: {0}".format(methodTypeStr)

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
    """.format(className, description, objectType, methodTypeStr, methodReturn, cppClassName))

# ---------------

def staticMethodObject(className,description,objectType, methodType,methodReturn, cppClassName):
    fileName = "../build/doc/"+objectType+".pddoc"
    outputFile = open(fileName,"w+")

    methodTypeStr = ",".join(methodType)
    methodTypeStr.replace("<","(")
    methodTypeStr.replace(">",")")
    methodReturn.replace("<","(")
    methodReturn.replace(">",")")

    if methodType == "[]":
        methodTypeStr = "accepts bang"
    else:
        methodTypeStr = "accepts list: {0}".format(methodTypeStr)

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
    """.format(className,description,objectType, methodTypeStr,methodReturn, cppClassName))
# ----------

def customClassObject(className,description,objectType, infoString):
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
