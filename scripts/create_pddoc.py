#!/usr/bin/python
import sys
import os
import re

sys.path = ["../"] + sys.path

import CppHeaderParser3 as CppHeaderParser
import common_functions as gen

import write_pddoc as docwrite

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

for filename in gen.getHeaderFiles():#os.listdir("../to_wrap/"):
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

            pdObjectName = gen.getClassNamePD(m["namespace"], m["name"]) #gen.convertName(m["name"])

            methodType = [t["type"] for t in m["parameters"]]
            methodReturn = m["rtnType"]

            methodInfoString = "("+" ".join(methodType)+")->"+methodReturn

            methodName = m["name"]

            docwrite.staticMethodObject("function", "", pdObjectName, methodType,methodReturn,"function")

            dbFile.write("{0} . ..\n".format(pdObjectName))


        for c in cppHeader.classes:
            className = c

            nameSpace = cppHeader.classes[c]["namespace"]

            #stub:
            if hasDefaultConstructor(cppHeader.classes[c]):
                docwrite.classObject(c, "no description", gen.getClassNamePD(nameSpace, className))
                dbFile.write("{0} . .\n".format(gen.convertName(c)))

            for m in cppHeader.classes[c]["methods"]["public"]:
                if m["template"] != False:
                    continue

                pdObjectName = gen.getClassNamePD(m["namespace"], className)+"."+gen.convertName(m["name"])

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
                    pdObjectName = gen.getClassNamePD(nameSpace, className)+".new"
                    docwrite.customClassObject(gen.getClassNameCXX(nameSpace, className), "", pdObjectName, methodInfoString)
                    dbFile.write("{0} . .\n".format(pdObjectName))
                    continue

                if m["static"] == True:
                    docwrite.staticMethodObject(gen.convertName(c), "", pdObjectName, methodType, methodReturn, c)
                else:
                    docwrite.classMethodObject(gen.convertName(c), "", pdObjectName, methodType, methodReturn, c)

                dbFile.write("{0} . ..\n".format(pdObjectName))
