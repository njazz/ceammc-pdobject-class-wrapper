#!/usr/bin/python
import sys
import os
import re

sys.path = ["../"] + sys.path

import CppHeaderParser

outputFile = open("../to_wrap/_generated.cpp","w+")
outputFile.write("#include \"Wrapper.hpp\"\n")
outputFile.write("#include \"DemoClass.hpp\"\n\n")

outputFile.write("extern \"C\"{\n");
outputFile.write("void setup(){\n\n")

patchFile = open("../build/_generated.pd","w+")
patchFile.write("#N canvas 320 320 640 480 12;\n")
patchFile.write("#X declare -lib wrapper_library;\n")
patchFile.write("#X obj 15 15 declare -lib wrapper_library;\n")
objectIndex = 1

patchYPos = 15 + 30
patchXPos = 15

def convert_name_h(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1-\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1-\2', s1).lower()

def convert_name_n(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1\2', s1).lower()

###

for filename in os.listdir("../to_wrap/"):
    if filename.endswith(".hpp"):
        # ###
        outputFile.write("// "+filename+"\n")
        patchFile.write("#X text 15 "+str(patchYPos)+ " "+filename+";\n")
        patchYPos += 30

        try:
            cppHeader = CppHeaderParser.CppHeader("../to_wrap/"+filename)
        except CppHeaderParser.CppParseError as e:
            print(e)
            sys.exit(1)

        # print("CppHeaderParser view of %s"%cppHeader)

        for c in cppHeader.classes:
            className = c
            outputFile.write("\n// Class: "+className+"\n")
            patchFile.write("#X text "+str(patchXPos+100)+" "+str(patchYPos)+ " \ "+className+";\n")
            objectIndex += 1

            patchYPos += 30

            outputFile.write("//\n")
            outputFile.write("WRAP_CLASS("+c+" , \""+convert_name_h(c)+"\");\n")
            patchFile.write("#X obj "+str(patchXPos+75)+" "+str(patchYPos-30)+ " ui.bang;\n")
            patchFile.write("#X obj "+str(patchXPos+75)+" "+str(patchYPos)+ " "+convert_name_h(c)+";\n")
            patchFile.write("#X obj "+str(patchXPos+75)+" "+str(patchYPos+25)+ " ui.display;\n")

            classObjectIndex = objectIndex+2
            patchFile.write("#X connect "+str(objectIndex+1)+" 0 "+str(objectIndex+2)+" 0;")
            patchFile.write("#X connect "+str(objectIndex+2)+" 0 "+str(objectIndex+3)+" 0;")
            objectIndex += 3

            patchYPos += 30
            patchYPos += 30

            methodIndex = 0

            for m in cppHeader.classes[c]["methods"]["public"]:
                methodName = m["name"]

                #todo: add & for references
                methodType = [t["type"] for t in m["parameters"]] #m["parameters"]
                # methodTypeRaw = [t["raw_type"] for t in m["parameters"]] #m["parameters"]
                methodReturn = m["rtnType"]
                # methodReturnRaw = m["rtnType"][0:3] #LOL

                # exclude constructors now:
                if methodName == className:
                    continue

                # exclude operators now:
                if methodName.startswith("operator"):
                    continue

                if m["const"] == True:
                    continue

                if m["static"] == True:
                    methodReturn = methodReturn.replace('static ','')
                    #continue

                methodPointerName = "_M"+className+"__"+methodName+"__"+str(methodIndex)  #"_".join(methodTypeRaw)+"__"+methodReturnRaw
                methodIndex+=1

                if m["static"] == False:
                    methodPointer = methodReturn + "("+className+"::*)(" + ",".join(methodType) + ")"
                else:
                    methodPointer = methodReturn + "(*)(" + ",".join(methodType) + ")"

                if m["static"] == False:
                    methodPointerDeclare = methodReturn + "("+className+"::*"+methodPointerName+")(" + ",".join(methodType) + ")"
                else:
                    methodPointerDeclare = methodReturn + "("+"*"+methodPointerName+")(" + ",".join(methodType) + ")"

                methodDeclare = "constexpr " + methodPointerDeclare + " "
                methodDeclare += "" #"_"+className+"_method_"+methodName

                if m["static"] == False:
                    methodDeclare += " = " + "static_cast<" + methodPointer + ">(&" +className+"::"+methodName+");"
                else:
                    methodDeclare += " = " + "static_cast<" + methodPointer + ">(&" +className+"::"+methodName+");"

                if m["static"] == False:
                    typeDeclare = "using "+methodPointerName+"_type = "+ methodReturn + "("+className+"::*const)(" + ",".join(methodType) + ");\n"
                else:
                    typeDeclare = "using "+methodPointerName+"_type = "+ methodReturn + "(*)(" + ",".join(methodType) + ");\n"

                outputFile.write(typeDeclare)

                outputFile.write(""+methodDeclare +"\n")

                pdObjectName = convert_name_h(c)+"."+convert_name_n(m["name"])

                wrapName = "WRAP_METHOD"
                if m["static"] == True:
                    wrapName = "WRAP_STATIC_METHOD"
                outputFile.write(wrapName+"(" + className + " , " + m["name"]+" , \"" + pdObjectName+"\","+methodPointerName+","+methodPointerName+"_type);\n")
                patchFile.write("#X obj "+str(patchXPos)+" "+str(patchYPos)+ " "+convert_name_n(pdObjectName)+";\n")
                objectIndex += 1

                patchFile.write("#X connect "+str(classObjectIndex)+" 0 "+str(objectIndex)+" 0;")

                patchYPos += 60

                outputFile.write("\n")

            outputFile.write("\n")

            patchXPos += 210
            patchYPos =  75

        continue
    else:
        continue

outputFile.write("}\n")
outputFile.write("}")
