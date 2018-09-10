#!/usr/bin/python
import sys
import os
import re

#TODO: template XML files

import common_functions as gen

global __outputDir__
__outputDir__ = ""

global __libraryConfig__

def escapeTypeString(typeString):
    ret = typeString.replace("<","(")
    ret = ret.replace(">",")")
    ret = ret.replace("&","(reference)")
    ret = ret.replace("*","(pointer)")
    return ret

# ---------------
def classObject(name,description,objectType):
    global __outputDir__
    global __libraryConfig__

    fileName = __outputDir__+objectType+".pddoc"
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
                <author>{CFG_AUTHORS}</author>
            </authors>
            <description>Instance of {CLASSNAME_CXX} object.</description>
            <license>{CFG_LICENSE}</license>
            <library>{CFG_LIBRARY}</library>
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
[declare -lib {CFG_LIBRARY}]

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
    """.format(CLASSNAME_CXX = name, \
    DESCR = description, \
    CLASSNAME_PD = objectType, \
    CFG_AUTHORS = __libraryConfig__["authors"], \
    CFG_LICENSE = __libraryConfig__["license"], \
    CFG_LIBRARY = __libraryConfig__["library_name"]))

#----------
def dataStorage(name,description,objectType):
    global __outputDir__
    global __libraryConfig__

# 1 local
    fileName = __outputDir__+"local."+objectType+".pddoc"
    outputFile = open(fileName,"w+")
    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="local.{CLASSNAME_PD}">
        <title>local.{CLASSNAME_PD}</title>
        <info>
            <par>{DESCR}</par>
        </info>
        <meta>
            <authors>
                <author>{CFG_AUTHORS}</author>
            </authors>
            <description>Local storage for {CLASSNAME_CXX} data.</description>
            <license>{CFG_LICENSE}</license>
            <library>{CFG_LIBRARY}</library>
            <category>local</category>
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
[declare -lib {CFG_LIBRARY}]

[B]
|
[local.{CLASSNAME_PD} storage-name]
|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(CLASSNAME_CXX = name, \
    DESCR = description, \
    CLASSNAME_PD = objectType, \
    CFG_AUTHORS = __libraryConfig__["authors"], \
    CFG_LICENSE = __libraryConfig__["license"], \
    CFG_LIBRARY = __libraryConfig__["library_name"]))

# 2 global
    fileName = __outputDir__+"global."+objectType+".pddoc"
    outputFile = open(fileName,"w+")
    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="global.{CLASSNAME_PD}">
        <title>global.{CLASSNAME_PD}</title>
        <info>
            <par>{DESCR}</par>
        </info>
        <meta>
            <authors>
                <author>{CFG_AUTHORS}</author>
            </authors>
            <description>Global storage for {CLASSNAME_CXX} data.</description>
            <license>{CFG_LICENSE}</license>
            <library>{CFG_LIBRARY}</library>
            <category>global</category>
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
[declare -lib {CFG_LIBRARY}]

[B]
|
[global.{CLASSNAME_PD} storage-name]
|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(CLASSNAME_CXX = name, \
    DESCR = description, \
    CLASSNAME_PD = objectType, \
    CFG_AUTHORS = __libraryConfig__["authors"], \
    CFG_LICENSE = __libraryConfig__["license"], \
    CFG_LIBRARY = __libraryConfig__["library_name"]))

#----------

def classMethodObject(className,description,objectType,methodType,methodReturn, cppClassName):
    global __outputDir__
    global __libraryConfig__

    fileName = __outputDir__+objectType+".pddoc"
    outputFile = open(fileName,"w+")

    methodTypeStr = ",".join(methodType)
    methodTypeStr = escapeTypeString(methodTypeStr)

    methodReturnStr = escapeTypeString(str(methodReturn))

    if methodType == []:
        methodTypeStr = "accepts bang"
    else:
        methodTypeStr = "accepts list: {0}".format(methodTypeStr)

    if methodReturn == []:
        methodReturnStr = "no output"
    else:
        methodReturnStr = "list: {0}".format(methodReturnStr)

    # print("object {0} args [{1}] return [{2}]".format(objectType, methodTypeStr, methodReturnStr))

    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="{OBJECTNAME_PD}">
        <title>{OBJECTNAME_PD}</title>
        <info>
            <par>{DESCR}</par>
        </info>
        <meta>
            <authors>
                <author>{CFG_AUTHORS}</author>
            </authors>
            <description>Method of {CLASSNAME_CXX}</description>
            <license>{CFG_LICENSE}</license>
            <library>{CFG_LIBRARY}</library>
            <category>{CLASSNAME_PD}</category>
            <keywords> none </keywords>
            <since> 1.0 </since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="any">{METHOD_ARGS_STR} </xinfo>
                <xinfo on="symbol">'func' outputs object's function as DataAtom at second outlet</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>{METHOD_RETURN_STR}</outlet>
            <outlet>Outputs DataAtom with {OBJECTNAME_PD} function.</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib {CFG_LIBRARY}]

[B]
|
[{CLASSNAME_PD}]
|  |
|  [ui.display @display_type 1]
|
|  [B] [1.0( [symbol test( [1 2 3(
|  |   |     |             |
[{OBJECTNAME_PD}                        ]
|
[ui.display @display_type 1]

[func(
|
[{OBJECTNAME_PD}]
^|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(CLASSNAME_PD = className, \
    DESCR = description, \
    OBJECTNAME_PD = objectType, \
    METHOD_ARGS_STR = methodTypeStr, \
    METHOD_RETURN_STR = methodReturnStr,
    CLASSNAME_CXX =cppClassName, \
    CFG_AUTHORS = __libraryConfig__["authors"], \
    CFG_LICENSE = __libraryConfig__["license"], \
    CFG_LIBRARY = __libraryConfig__["library_name"]))

# ---------------

def staticMethodObject(className,description,objectType, methodType,methodReturn, cppClassName):
    global __outputDir__
    global __libraryConfig__

    fileName = __outputDir__+objectType+".pddoc"
    outputFile = open(fileName,"w+")

    methodTypeStr = ",".join(methodType)
    methodTypeStr = escapeTypeString(methodTypeStr)

    methodReturnStr = escapeTypeString(str(methodReturn))

    if methodType ==  []:
        methodTypeStr = "accepts bang"
    else:
        methodTypeStr = "accepts list: {0}".format(methodTypeStr)

    if methodReturn == []:
        methodReturn = "no output"
    else:
        methodReturn = "list: {0}".format(methodReturn)

    outputFile.write("""<?xml version="1.0" encoding="utf-8"?>
<pddoc version="1.0">
    <object name="{OBJECTNAME_PD}">
        <title>{OBJECTNAME_PD}</title>
        <info>
            <par>{DESCR}</par>
        </info>
        <meta>
            <authors>
                <author>{CFG_AUTHORS}</author>
            </authors>
            <description>Static method of {CLASSNAME_CXX}</description>
            <license>{CFG_LICENSE}</license>
            <library>{CFG_LIBRARY}</library>
            <category>{CLASSNAME_PD}</category>
            <keywords>none</keywords>
            <since>1.0</since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="any">{METHOD_ARGS_STR} </xinfo>
                <xinfo on="symbol">'thread 1' sets the object to perform it's action in separate thread</xinfo>
                <xinfo on="symbol">'func' outputs object's function as DataAtom at second outlet</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>{METHOD_RETURN_STR}</outlet>
            <outlet>Outputs DataAtom with {OBJECTNAME_PD} function.</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib {CFG_LIBRARY}]

[B] [1.0( [symbol test( [1 2 3(
|   |     |             |
[{OBJECTNAME_PD}                               ]
|
[ui.display @display_type 1]

[loadbang]
|
[thread 1(
|
|  [B] [1.0( [symbol test( [1 2 3(
|  |   |     |             |
[{OBJECTNAME_PD}                               ]
|
[ui.display @display_type 1]

[func(
|
[{OBJECTNAME_PD}]
^|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(CLASSNAME_PD = className, \
    DESCR = description, \
    OBJECTNAME_PD = objectType, \
    METHOD_ARGS_STR = methodTypeStr, \
    METHOD_RETURN_STR = methodReturnStr,
    CLASSNAME_CXX =cppClassName, \
    CFG_AUTHORS = __libraryConfig__["authors"], \
    CFG_LICENSE = __libraryConfig__["license"], \
    CFG_LIBRARY = __libraryConfig__["library_name"]))
# ----------

def customClassObject(className,description,objectType, infoString):
    global __outputDir__
    global __libraryConfig__

    fileName = __outputDir__+objectType+".pddoc"
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
                <author>{CFG_AUTHORS}</author>
            </authors>
            <description>Creates new instances of {CLASSNAME_CXX}</description>
            <license>{CFG_LICENSE}</license>
            <library>{CFG_LIBRARY}</library>
            <category>{CLASSNAME_CXX}</category>
            <keywords> none </keywords>
            <since> 1.0 </since>
        </meta>
        <inlets>
            <inlet>
                <xinfo on="bang">Outputs current instance of {CLASSNAME_CXX} </xinfo>
                <xinfo on="any">Creates new instance of {CLASSNAME_CXX} and outputs it</xinfo>
            </inlet>
        </inlets>
        <outlets>
            <outlet>Outputs DataAtom with {CLASSNAME_CXX} object.</outlet>
        </outlets>
        <example>
            <pdascii>
<![CDATA[
[declare -lib {CFG_LIBRARY}]

[B] [1.0( [symbol test( [1 2 3(
|   |     |             |
[{CLASSNAME_PD}                        ]
|
[ui.display @display_type 1]

]]>
            </pdascii>
        </example>
    </object>
</pddoc>
    """.format(CLASSNAME_CXX = className, \
    DESCR = description, \
    CLASSNAME_PD = objectType, \
    INFO_STRING = infoString, \
    CFG_AUTHORS = __libraryConfig__["authors"], \
    CFG_LICENSE = __libraryConfig__["license"], \
    CFG_LIBRARY = __libraryConfig__["library_name"]))
