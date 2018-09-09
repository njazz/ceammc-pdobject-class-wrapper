#!/usr/bin/python

import sys
import os
import re

# camelCase -> camel-case
def convertNameWithH(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1-\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1-\2', s1).lower()

# camelCase -> camelcase
def convertName(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1\2', s1).lower()

def getHeaderFiles():
    ret = os.listdir("../to_wrap/")
    try:
        ret = ret + os.listdir("../../to_wrap/")
    except:
        print()

    return ret;

# TODO: test this
def getHeaderFilesFullPath():
    ret = []
    files = os.listdir("../to_wrap/")
    for filename in files:
        if filename.endswith(".hpp") or filename.endswith(".h"):
            ret += ["../to_wrap/"+filename]

    try:
        files = os.listdir("../../to_wrap/")
        for filename in files:
            if filename.endswith(".hpp") or filename.endswith(".h"):
                ret += ["../../to_wrap/"+filename]
    except:
        print()

    return ret;

#####
# def getPdObjectName(cxxClassName):
#     return "object"
#
# def getPdObjectName(cxxClassName, cxxMethodName):
#     return "object.method"
#####

def getClassNameCXX(nameSpace, classNameSrc):
    nameSpaceDivider = "::"
    if (nameSpace == ""):
        nameSpaceDivider = ""
    if len(nameSpace) > 0:
        ret = nameSpace + "::" + classNameSrc
    else:
        ret = classNameSrc
    return ret

def getClassNamePD(nameSpace, classNameSrc):
    ret = convertName(getClassNameCXX(nameSpace, classNameSrc))
    ret = ret.replace("::",".")
    return ret
