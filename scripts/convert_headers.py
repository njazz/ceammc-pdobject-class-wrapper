#!/usr/bin/python
import sys
import os
import re

sys.path = ["../"] + sys.path

import CppHeaderParser3 as CppHeaderParser
import common_functions as gen
import converter_object_templates as objt

#TODO converter templates

# ------------

def outputWriteHeader(file):
    file.write("#include \"Wrapper.hpp\"\n\n")
    for filename in os.listdir("../to_wrap/"):
        if filename.endswith(".hpp") or filename.endswith(".h"):
            file.write("#include \""+filename+"\"\n")

    file.write("extern \"C\"{\n");
    file.write("void setup(){\n\n")

# ------------

outputFile = open("../generated/generated.cpp","w+")

outputWriteHeader(outputFile)

for filename in gen.getHeaderFiles(): #os.listdir("../to_wrap/"):
    if filename.endswith(".hpp") or filename.endswith(".h"):
        outputFile.write("// "+filename+"\n")

        try:
            cppHeader = CppHeaderParser.CppHeader("../to_wrap/"+filename)
        except CppHeaderParser.CppParseError as e:
            print(e)
            sys.exit(1)

# debug:
#        print("CppHeaderParser view of %s"%cppHeader)

        methodIndex = 0

        # ----------
        # plain functions

        for f in cppHeader.functions:
            functionName = f["name"]
            nameSpace = f["namespace"]

            m = f
            if m["template"] != False:
                continue

            methodName = f["name"]

            #todo: add & for references
            methodType = [t["type"] for t in m["parameters"]]
            methodReturn = m["rtnType"]

            # exclude operators now:
            if methodName.startswith("operator"):
                continue

            if m["static"] == True:
                methodReturn = methodReturn.replace('static ','')

            if m["inline"] == True:
                methodReturn = methodReturn.replace('inline ','')

            methodName = gen.getClassNameCXX(nameSpace, m["name"])
            pdObjectName = gen.getClassNamePD(nameSpace, m["name"]) #gen.convertName(m["name"])

            toWrite = objt.genFunc(methodName, nameSpace, pdObjectName, methodIndex, methodReturn, ",".join(methodType))
            outputFile.write(toWrite)

            methodIndex+=1


        # -----------------

        for c in cppHeader.classes:

            className = c
            nameSpace = cppHeader.classes[c]["namespace"]

            # todo: clean up
            justClassName = c

            nameCXX = gen.getClassNameCXX(nameSpace, className)
            namePD = gen.getClassNamePD(nameSpace, className)

            hasDefaultConstructor = False
            hasConstructor = False
            for m in cppHeader.classes[c]["methods"]["public"]:

                if m["constructor"]:
                    hasConstructor = True
                    methodType = [t["type"] for t in m["parameters"]]
                    if methodType == "":
                        hasDefaultConstructor = True
                        continue
            #implicit
            if (not hasConstructor) and (not hasDefaultConstructor):
                hasDefaultConstructor = True

            #####
            if hasDefaultConstructor:
                outputFile.write(objt.genClass(nameCXX,c, namePD))

            methodIndex = 0

            # fix:
            nameSpace = nameSpace.lstrip(':')

            if len(nameSpace) > 0:
                className = nameSpace+"::"+c

            # ----------
            # fields

            for m in cppHeader.classes[c]["properties"]["public"]:
                methodName = m["name"]

                #todo: add & for references
                methodType = [t["type"] for t in m["parameters"]]
                methodReturn = m["rtnType"]

                wrapName = "WRAP_FIELD"

                lastClassName = className.split("::")[-1]

                if m["const"] == True:
                    wrapName = "WRAP_CONST_FIELD"

                if m["static"] == True:
                    methodReturn = methodReturn.replace('static ','')

                if m["inline"] == True:
                    methodReturn = methodReturn.replace('inline ','')

                nameSpaceDivider = ''
                if len(nameSpace) > 0:
                    nameSpaceDivider = "::"
                methodPointerName = nameSpace + nameSpaceDivider+ "_M"+justClassName+"__"+methodName+"__"+str(methodIndex)  #"_".join(methodTypeRaw)+"__"+methodReturnRaw
                methodPointerNameWithoutNS = justClassName+"__"+methodName+"__"+str(methodIndex)+"_M"
                # another fix:
                methodPointerNameWithoutNS = methodPointerNameWithoutNS.replace(":","_")
                methodIndex+=1

                # todo

            # ----------
            # methods

            for m in cppHeader.classes[c]["methods"]["public"]:
                if m["template"] != False:
                    continue

                methodName = m["name"]

                #todo: add & for references
                methodType = [t["type"] for t in m["parameters"]]
                methodReturn = m["rtnType"]

                wrapName = "WRAP_METHOD"
                customConstructor = False

                lastClassName = className.split("::")[-1]
                # outputFile.write("// method name / class name " + methodName + " "+justClassName +"\n")

                # custom constructor
                if methodName == lastClassName:
                    #exclude default
                    if methodType == "":
                        continue
                    wrapName = "WRAP_CUSTOM_CLASS"
                    customConstructor = True

                # exclude operators now:
                if methodName.startswith("operator"):
                    continue

                if m["const"] == True:
                    continue

                if m["static"] == True:
                    methodReturn = methodReturn.replace('static ','')

                if m["inline"] == True:
                    methodReturn = methodReturn.replace('inline ','')

                nameSpaceDivider = ''
                if len(nameSpace) > 0:
                    nameSpaceDivider = "::"
                methodPointerName = nameSpace + nameSpaceDivider+ "_M"+justClassName+"__"+methodName+"__"+str(methodIndex)  #"_".join(methodTypeRaw)+"__"+methodReturnRaw
                methodPointerNameWithoutNS = justClassName+"__"+methodName+"__"+str(methodIndex)+"_M"
                # another fix:
                methodPointerNameWithoutNS = methodPointerNameWithoutNS.replace(":","_")
                methodIndex+=1

                if m["static"] == True:
                    wrapName = "WRAP_STATIC_METHOD"
                    methodPointer = methodReturn + "(*)(" + ",".join(methodType) + ")"
                    methodPointerDeclare = methodReturn + "("+"*"+methodPointerNameWithoutNS+")(" + ",".join(methodType) + ")"
                    methodDeclare = "constexpr " + methodPointerDeclare + " "
                    methodDeclare += " = " + "static_cast<" + methodPointer + ">(&" +className+"::"+methodName+");"
                    typeDeclare = "using "+methodPointerNameWithoutNS+"_type = "+ methodReturn + "(*)(" + ",".join(methodType) + ");\n"

                    # outputFile.write(objt.)
                else:
                    methodPointer = methodReturn + "("+className+"::*)(" + ",".join(methodType) + ")"
                    methodPointerDeclare = methodReturn + "("+className+"::*"+methodPointerNameWithoutNS+")(" + ",".join(methodType) + ")"
                    methodDeclare = "constexpr " + methodPointerDeclare + " "
                    methodDeclare += " = " + "static_cast<" + methodPointer + ">(&" +className+"::"+methodName+");"
                    typeDeclare = "using "+methodPointerNameWithoutNS+"_type = "+ methodReturn + "("+className+"::*)(" + ",".join(methodType) + ");\n"

                outputFile.write(typeDeclare)
                if customConstructor == False:
                    outputFile.write(""+methodDeclare +"\n")

                pdObjectName = gen.convertName(c)+"."+gen.convertName(m["name"])
                if customConstructor == True:
                    pdObjectName = gen.convertName(c)+".new"

                outputFile.write(wrapName+"(" + className + " , " + m["name"]+" , \"" + pdObjectName+"\","+methodPointerNameWithoutNS+","+methodPointerNameWithoutNS+"_type);\n")

                staticObjOffset = int(m["static"])*60

                # methodInfoString = "("+" ".join(methodType)+")->"+methodReturn

                outputFile.write("\n")

            outputFile.write("\n")

        continue
    else:
        continue

outputFile.write("}\n")
outputFile.write("}")
