#!/usr/bin/python
import sys
import os
import re

# using _func_test_function_wrapper__0_M_type = float(*)(void *);
# constexpr auto _func_test_function_wrapper__0_M  = &test_function_wrapper;
# WRAP_FUNCTION( test_function_wrapper , "test_function_wrapper",_func_test_function_wrapper__0_M,_func_test_function_wrapper__0_M_type);
funcTemplate = """
// Function: {FUNCTIONNAME_CXX}
// Namespace: {NAMESPACE}
using _func_{FUNCTIONNAME_PD}__{IDX}_M_type = {FUNC_RETURN}(*)({FUNC_ARGS});
constexpr auto _func_{FUNCTIONNAME_PD}__{IDX}_M  = &{FUNCTIONNAME_PD};
WRAP_FUNCTION({FUNCTIONNAME_PD}, "{FUNCTIONNAME_PD}", _func_{FUNCTIONNAME_PD}__{IDX}_M, _func_{FUNCTIONNAME_PD}__{IDX}_M_type);
"""

def genFunc(funcNameCXX, nameSpace, funcNamePD, idx, funcReturn, funcArgs):
    return funcTemplate.format(FUNCTIONNAME_CXX = funcNameCXX, NAMESPACE = nameSpace, FUNCTIONNAME_PD = funcNamePD, IDX = idx, FUNC_RETURN = funcReturn, FUNC_ARGS = funcArgs )

# WRAP_CLASS(DemoSubClass , "demosubclass");
classTemplate = """
// Class: {CLASSNAME_CXX}
// Namespace: {NAMESPACE}
WRAP_CLASS({CLASSNAME_CXX} , "{CLASSNAME_PD}");

"""

def genClass(classNameCXX, nameSpace, classNamePD):
    return classTemplate.format(CLASSNAME_CXX = classNameCXX, NAMESPACE = nameSpace, CLASSNAME_PD = classNamePD)

# using DemoSubClass__ref__0_M_type = long &(DemoSubClass::*)();
# constexpr long &(DemoSubClass::*DemoSubClass__ref__0_M)()  = static_cast<long &(DemoSubClass::*)()>(&DemoSubClass::ref);
# WRAP_METHOD(DemoSubClass , ref , "demosubclass.ref",DemoSubClass__ref__0_M,DemoSubClass__ref__0_M_type);
classMethodTemplate = """
using $CLASSNAME_PD__$METHODNAME_PD__$IDX_M_type = $METHOD_RETURN($CLASSNAME_CXX::*)($METHOD_ARGS);
constexpr $METHOD_RETURN($CLASSNAME_CXX::*$CLASSNAME_PD__$METHODNAME_PD__$IDX_M)($METHOD_ARGS)  = static_cast<$METHOD_RETURN($CLASSNAME_CXX::*)($METHOD_ARGS)>(&$CLASSNAME_CXX::$METHODNAME_CXX);
WRAP_METHOD($CLASSNAME_CXX, $METHODNAME_CXX, "$CLASSNAME_PD.$METHODNAME_PD", $CLASSNAME_PD__$METHODNAME_PD__$IDX_M, $CLASSNAME_CXX::*$CLASSNAME_PD__$METHODNAME_PD__$IDX_M_type);
"""

# using DemoClass__testStatic__7_M_type = std::string(*)(int);
# constexpr std::string(*DemoClass__testStatic__7_M)(int)  = static_cast<std::string(*)(int)>(&DemoClass::testStatic);
# WRAP_STATIC_METHOD(DemoClass , testStatic , "democlass.teststatic",DemoClass__testStatic__7_M,DemoClass__testStatic__7_M_type);
classStaticMethodTemplate = """
using $CLASSNAME_PD__$METHODNAME_PD__$IDX_M_type = $METHOD_RETURN(*)($METHOD_ARGS);
constexpr $METHOD_RETURN($CLASSNAME_CXX::*$CLASSNAME_PD__$METHODNAME_PD__$IDX_M)($METHOD_ARGS)  = static_cast<$METHOD_RETURN(*)($METHOD_ARGS)>(&$CLASSNAME_CXX::$METHODNAME_CXX);
WRAP_METHOD($CLASSNAME_CXX, $METHODNAME_CXX, "$CLASSNAME_PD.$METHODNAME_PD", $CLASSNAME_PD__$METHODNAME_PD__$IDX_M, $CLASSNAME_CXX::*$CLASSNAME_PD__$METHODNAME_PD__$IDX_M_type);
"""

# using WithConstructor__WithConstructor__0_M_type = void(WithConstructor::*)(float);
# WRAP_CUSTOM_CLASS(WithConstructor , WithConstructor , "withconstructor.new",WithConstructor__WithConstructor__0_M,WithConstructor__WithConstructor__0_M_type);
customClassTemplate = """
// Class: WithConstructor
// Namespace: []
using $CLASSNAME_PD_$IDX_constructor_type = $METHOD_RETURN($CLASSNAME_CXX::*)($METHOD_ARGS);
WRAP_CUSTOM_CLASS($CLASSNAME_CXX, $CLASSNAME_CXX, "$CLASSNAME_PD.new", $CLASSNAME_PD_$IDX_constructor, $CLASSNAME_PD_$IDX_constructor_type);
"""
