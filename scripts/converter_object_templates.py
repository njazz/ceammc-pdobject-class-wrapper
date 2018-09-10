#!/usr/bin/python
import sys
import os
import re

import common_functions as gen

# using _func_test_function_wrapper__0_M_type = float(*)(void *);
# constexpr auto _func_test_function_wrapper__0_M  = &test_function_wrapper;
# WRAP_FUNCTION( test_function_wrapper , "test_function_wrapper",_func_test_function_wrapper__0_M,_func_test_function_wrapper__0_M_type);
funcTemplate = """
// Function: {FUNCTIONNAME_CXX}
// Namespace: {NAMESPACE}
using _func_{FUNCTIONNAME_PD}__{IDX}_M_type = {FUNC_RETURN}(*)({FUNC_ARGS});
constexpr auto _func_{FUNCTIONNAME_PD}__{IDX}_M  = &{FUNCTIONNAME_CXX};
WRAP_FUNCTION({FUNCTIONNAME_PD}, "{FUNCTIONNAME_PD}", _func_{FUNCTIONNAME_PD}__{IDX}_M, _func_{FUNCTIONNAME_PD}__{IDX}_M_type);
"""

def genFunc(nameSpace, funcNameSrc,  idx, funcReturn, funcArgs):
    funcNameCXX = gen.getClassNameCXX(nameSpace, funcNameSrc)
    funcNamePD = gen.getClassNamePD(nameSpace, funcNameSrc)
    return funcTemplate.format(FUNCTIONNAME_CXX = funcNameCXX, NAMESPACE = nameSpace, FUNCTIONNAME_PD = funcNamePD, IDX = idx, FUNC_RETURN = funcReturn, FUNC_ARGS = funcArgs )

# WRAP_CLASS(DemoSubClass , "demosubclass");
classTemplate = """
// Class: {CLASSNAME_CXX}
// Namespace: {NAMESPACE}
WRAP_CLASS({CLASSNAME_CXX}, "{CLASSNAME_PD}");
WRAP_STORAGE({CLASSNAME_CXX}, {CLASSNAME_STR}, "{CLASSNAME_PD}");
"""

def genClass(nameSpace, classNameSrc):
    classNameCXX = gen.getClassNameCXX(nameSpace, classNameSrc)
    classNamePD = gen.getClassNamePD(nameSpace, classNameSrc)
    classNameStr = gen.escapeTypeStringForTypeName(classNameSrc)
    return classTemplate.format(CLASSNAME_CXX = classNameCXX, NAMESPACE = nameSpace, CLASSNAME_STR = classNameStr, CLASSNAME_PD = classNamePD)

# using DemoSubClass__ref__0_M_type = long &(DemoSubClass::*)();
# constexpr long &(DemoSubClass::*DemoSubClass__ref__0_M)()  = static_cast<long &(DemoSubClass::*)()>(&DemoSubClass::ref);
# WRAP_METHOD(DemoSubClass , ref , "demosubclass.ref",DemoSubClass__ref__0_M,DemoSubClass__ref__0_M_type);
classMethodTemplate = """
using {CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M_type = {METHOD_RETURN}({CLASSNAME_CXX}::*)({METHOD_ARGS});
constexpr {METHOD_RETURN}({CLASSNAME_CXX}::*{CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M)({METHOD_ARGS})  = static_cast<{METHOD_RETURN}({CLASSNAME_CXX}::*)({METHOD_ARGS})>(&{CLASSNAME_CXX}::{METHODNAME_CXX});
WRAP_METHOD({CLASSNAME_CXX}, {METHODNAME_CXX}, "{CLASSNAME_PD}.{METHODNAME_PD}", {CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M, {CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M_type);
"""

def genClassMethod(nameSpace, classNameSrc, idx, methodNameSrc, methodReturn, methodArgs):
    classNameCXX = gen.getClassNameCXX(nameSpace, classNameSrc)
    classNamePD = gen.getClassNamePD(nameSpace, classNameSrc)
    classNameLetters = classNamePD.replace(".","_")
    methodNameCXX = methodNameSrc
    methodNamePD = gen.convertName(methodNameSrc)
    methodNameLetters = methodNamePD.replace(".","_")
    #
    return classMethodTemplate.format(NAMESPACE = nameSpace, \
    CLASSNAME_CXX = classNameCXX, \
    CLASSNAME_PD = classNamePD, \
    CLASSNAME_LETTERS = classNameLetters, \
    METHODNAME_CXX = methodNameCXX, \
    METHODNAME_PD = methodNamePD, \
    METHODNAME_LETTERS = methodNameLetters, \
    IDX = idx, \
    METHOD_RETURN = methodReturn, \
    METHOD_ARGS = methodArgs)

# using DemoClass__testStatic__7_M_type = std::string(*)(int);
# constexpr std::string(*DemoClass__testStatic__7_M)(int)  = static_cast<std::string(*)(int)>(&DemoClass::testStatic);
# WRAP_STATIC_METHOD(DemoClass , testStatic , "democlass.teststatic",DemoClass__testStatic__7_M,DemoClass__testStatic__7_M_type);
classStaticMethodTemplate = """
using {CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M_type = {METHOD_RETURN}(*)({METHOD_ARGS});
constexpr {METHOD_RETURN}(*{CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M)({METHOD_ARGS})  = (&{CLASSNAME_CXX}::{METHODNAME_CXX});
WRAP_STATIC_METHOD({CLASSNAME_CXX}, {METHODNAME_CXX}, "{CLASSNAME_PD}.{METHODNAME_PD}", {CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M, {CLASSNAME_LETTERS}__{METHODNAME_LETTERS}__{IDX}_M_type);
"""

def genClassStaticMethod(nameSpace, classNameSrc, idx, methodNameSrc, methodReturn, methodArgs):
    classNameCXX = gen.getClassNameCXX(nameSpace, classNameSrc)
    classNamePD = gen.getClassNamePD(nameSpace, classNameSrc)
    classNameLetters = classNamePD.replace(".","_")
    methodNameCXX = methodNameSrc
    methodNamePD = gen.convertName(methodNameSrc)
    methodNameLetters = methodNamePD.replace(".","_")
    #
    return classStaticMethodTemplate.format(NAMESPACE = nameSpace, \
    CLASSNAME_CXX = classNameCXX, \
    CLASSNAME_PD = classNamePD, \
    CLASSNAME_LETTERS = classNameLetters, \
    METHODNAME_CXX = methodNameCXX, \
    METHODNAME_PD = methodNamePD, \
    METHODNAME_LETTERS = methodNameLetters, \
    IDX = idx, \
    METHOD_RETURN = methodReturn, \
    METHOD_ARGS = methodArgs)

# using WithConstructor__WithConstructor__0_M_type = void(WithConstructor::*)(float);
# WRAP_CUSTOM_CLASS(WithConstructor , WithConstructor , "withconstructor.new",WithConstructor__WithConstructor__0_M,WithConstructor__WithConstructor__0_M_type);

# TODO: {CLASSNAME_PD}_{IDX}_constructor is unused
customClassTemplate = """
// Class: {CLASSNAME_CXX}
// Namespace: {NAMESPACE}
using {CLASSNAME_LETTERS}_{IDX}_constructor_type = void({CLASSNAME_CXX}::*)({METHOD_ARGS});
WRAP_CUSTOM_CLASS({CLASSNAME_CXX}, {CONSTRUCTOR}, "{CLASSNAME_PD}.new", {CLASSNAME_LETTERS}_{IDX}_constructor, {CLASSNAME_LETTERS}_{IDX}_constructor_type);
"""

def genCustomClass(nameSpace, classNameSrc, idx, methodArgs):
    classNameCXX = gen.getClassNameCXX(nameSpace, classNameSrc)
    classNamePD = gen.getClassNamePD(nameSpace, classNameSrc)
    classNameLetters = classNamePD.replace(".","_")
    return customClassTemplate.format(CLASSNAME_CXX = classNameCXX, \
    CLASSNAME_PD = classNamePD, \
    CLASSNAME_LETTERS = classNameLetters, \
    CONSTRUCTOR = classNameSrc, \
    NAMESPACE = nameSpace, \
    IDX = idx, \
    METHOD_ARGS = methodArgs)
