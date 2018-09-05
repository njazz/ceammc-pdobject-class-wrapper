#!/usr/bin/python
import sys
import os
import re

sys.path = ["../"] + sys.path

import CppHeaderParser3 as CppHeaderParser

# camelCase -> camel-case
def convert_name_h(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1-\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1-\2', s1).lower()

# camelCase -> camelcase
def convert_name_n(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1\2', s1).lower()

# ------------

def outputWriteHeader(file):
    file.write("#include \"Wrapper.hpp\"\n\n")
    for filename in os.listdir("../to_wrap/"):
        if filename.endswith(".hpp"):
            file.write("#include \""+filename+"\"\n")

    file.write("extern \"C\"{\n");
    file.write("void setup(){\n\n")

# def patchWriteHeader(file):
#     file.write("#N canvas 100 100 800 600 12;\n")
#     file.write("#X declare -lib wrapper_library;\n")
#     file.write("#X obj 15 15 declare -lib wrapper_library;\n")

# ------------

outputFile = open("../to_wrap/_generated.cpp","w+")

outputWriteHeader(outputFile)
# patchWriteHeader(patchFile)

for filename in os.listdir("../to_wrap/"):
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
        for f in cppHeader.functions:
            functionName = f["name"]
            nameSpace = f["namespace"]

            outputFile.write("\n// Function: "+functionName+"\n")
            outputFile.write("// Namespace: ["+nameSpace+"]\n")

            m = f
            if m["template"] != False:
                continue

            methodName = f["name"]

            #todo: add & for references
            methodType = [t["type"] for t in m["parameters"]]
            methodReturn = m["rtnType"]

            wrapName = "WRAP_FUNCTION"

            # exclude operators now:
            if methodName.startswith("operator"):
                continue

            if m["static"] == True:
                methodReturn = methodReturn.replace('static ','')

            if m["inline"] == True:
                methodReturn = methodReturn.replace('inline ','')
                #continue

            nameSpaceDivider = ''
            if len(nameSpace) > 0:
                nameSpaceDivider = "::"
            methodPointerName = nameSpace + nameSpaceDivider+ "_M"+"_func_"+methodName+"__"+str(methodIndex)  #"_".join(methodTypeRaw)+"__"+methodReturnRaw
            methodPointerNameWithoutNS = "_func_"+methodName+"__"+str(methodIndex)+"_M"
            # another fix:
            methodPointerNameWithoutNS = methodPointerNameWithoutNS.replace(":","_")
            methodIndex+=1


            if m["static"] == False:
                methodPointer = methodReturn + "(*)(" + ",".join(methodType) + ")"
            else:
                methodPointer = methodReturn + "(*)(" + ",".join(methodType) + ")"

            if m["static"] == False:
                methodPointerDeclare = methodReturn + "(*"+methodPointerNameWithoutNS+")(" + ",".join(methodType) + ")"
            else:
                methodPointerDeclare = methodReturn + "(*"+methodPointerNameWithoutNS+")(" + ",".join(methodType) + ")"

            methodDeclare = "constexpr " + methodPointerDeclare + " "
            methodDeclare += "" #"_"+className+"_method_"+methodName

            if m["static"] == False:
                methodDeclare += " = " + "static_cast<" + methodPointer + ">(&"+methodName+");"
            else:
                methodDeclare += " = " + "static_cast<" + methodPointer + ">(&"+methodName+");"

            if m["static"] == False:
                typeDeclare = "using "+methodPointerNameWithoutNS+"_type = "+ methodReturn + "(*)(" + ",".join(methodType) + ");\n"
            else:
                typeDeclare = "using "+methodPointerNameWithoutNS+"_type = "+ methodReturn + "(*)(" + ",".join(methodType) + ");\n"

            outputFile.write(typeDeclare)
            # if customConstructor == False:
            outputFile.write(""+methodDeclare +"\n")

            pdObjectName = convert_name_n(m["name"])
            # if customConstructor == True:
            #     pdObjectName = convert_name_n(c)+".new"

            # if m["static"] == True:
            #     wrapName = "WRAP_STATIC_METHOD"

            outputFile.write(wrapName+"( " + m["name"]+" , \"" + pdObjectName+"\","+methodPointerNameWithoutNS+","+methodPointerNameWithoutNS+"_type);\n")

            staticObjOffset = int(m["static"])*60

            methodInfoString = "("+" ".join(methodType)+")->"+methodReturn

            outputFile.write("\n")


# -----------------

        for c in cppHeader.classes:

            className = c
            nameSpace = cppHeader.classes[c]["namespace"]
            # fix:
            nameSpace = nameSpace.lstrip(':')

            if len(nameSpace) > 0:
                className = nameSpace+"::"+c

            # todo: clean up
            justClassName = c

            outputFile.write("\n// Class: "+justClassName+"\n")
            outputFile.write("// Namespace: ["+nameSpace+"]\n")

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

            if hasDefaultConstructor:
                outputFile.write("WRAP_CLASS("+className+" , \""+convert_name_n(c)+"\");\n")

            methodIndex = 0

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
                    #continue

                nameSpaceDivider = ''
                if len(nameSpace) > 0:
                    nameSpaceDivider = "::"
                methodPointerName = nameSpace + nameSpaceDivider+ "_M"+justClassName+"__"+methodName+"__"+str(methodIndex)  #"_".join(methodTypeRaw)+"__"+methodReturnRaw
                methodPointerNameWithoutNS = justClassName+"__"+methodName+"__"+str(methodIndex)+"_M"
                # another fix:
                methodPointerNameWithoutNS = methodPointerNameWithoutNS.replace(":","_")
                methodIndex+=1


                if m["static"] == False:
                    methodPointer = methodReturn + "("+className+"::*)(" + ",".join(methodType) + ")"
                else:
                    methodPointer = methodReturn + "(*)(" + ",".join(methodType) + ")"

                if m["static"] == False:
                    methodPointerDeclare = methodReturn + "("+className+"::*"+methodPointerNameWithoutNS+")(" + ",".join(methodType) + ")"
                else:
                    methodPointerDeclare = methodReturn + "("+"*"+methodPointerNameWithoutNS+")(" + ",".join(methodType) + ")"

                methodDeclare = "constexpr " + methodPointerDeclare + " "
                methodDeclare += "" #"_"+className+"_method_"+methodName

                if m["static"] == False:
                    methodDeclare += " = " + "static_cast<" + methodPointer + ">(&" +className+"::"+methodName+");"
                else:
                    methodDeclare += " = " + "static_cast<" + methodPointer + ">(&" +className+"::"+methodName+");"

                if m["static"] == False:
                    typeDeclare = "using "+methodPointerNameWithoutNS+"_type = "+ methodReturn + "("+className+"::*)(" + ",".join(methodType) + ");\n"
                else:
                    typeDeclare = "using "+methodPointerNameWithoutNS+"_type = "+ methodReturn + "(*)(" + ",".join(methodType) + ");\n"

                outputFile.write(typeDeclare)
                if customConstructor == False:
                    outputFile.write(""+methodDeclare +"\n")

                pdObjectName = convert_name_n(c)+"."+convert_name_n(m["name"])
                if customConstructor == True:
                    pdObjectName = convert_name_n(c)+".new"

                if m["static"] == True:
                    wrapName = "WRAP_STATIC_METHOD"

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
