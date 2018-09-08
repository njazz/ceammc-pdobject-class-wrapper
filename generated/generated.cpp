#include "Wrapper.hpp"

#include "DemoClass.hpp"
extern "C"{
void setup(){

// DemoClass.hpp

// Function: test_function_wrapper
// Namespace: 
using _func_test_function_wrapper__0_M_type = float(*)(void *);
constexpr auto _func_test_function_wrapper__0_M  = &test_function_wrapper;
WRAP_FUNCTION(test_function_wrapper, "test_function_wrapper", _func_test_function_wrapper__0_M, _func_test_function_wrapper__0_M_type);

// Function: test_function_wrapper_v
// Namespace: 
using _func_test_function_wrapper_v__1_M_type = void(*)(void *);
constexpr auto _func_test_function_wrapper_v__1_M  = &test_function_wrapper_v;
WRAP_FUNCTION(test_function_wrapper_v, "test_function_wrapper_v", _func_test_function_wrapper_v__1_M, _func_test_function_wrapper_v__1_M_type);

// Function: test_function_wrapper_v_ptr
// Namespace: 
using _func_test_function_wrapper_v_ptr__2_M_type = void(*)(float(*ptr)(float));
constexpr auto _func_test_function_wrapper_v_ptr__2_M  = &test_function_wrapper_v_ptr;
WRAP_FUNCTION(test_function_wrapper_v_ptr, "test_function_wrapper_v_ptr", _func_test_function_wrapper_v_ptr__2_M, _func_test_function_wrapper_v_ptr__2_M_type);

// Function: test_function_wrapper_v_ptr_v
// Namespace: 
using _func_test_function_wrapper_v_ptr_v__3_M_type = void(*)(void(*ptr)(float));
constexpr auto _func_test_function_wrapper_v_ptr_v__3_M  = &test_function_wrapper_v_ptr_v;
WRAP_FUNCTION(test_function_wrapper_v_ptr_v, "test_function_wrapper_v_ptr_v", _func_test_function_wrapper_v_ptr_v__3_M, _func_test_function_wrapper_v_ptr_v__3_M_type);

// Function: test_macro1
// Namespace: 
using _func_test_macro1__4_M_type = MACRO_1(*)();
constexpr auto _func_test_macro1__4_M  = &test_macro1;
WRAP_FUNCTION(test_macro1, "test_macro1", _func_test_macro1__4_M, _func_test_macro1__4_M_type);

// Function: func_plus_10
// Namespace: 
using _func_func_plus_10__5_M_type = float(*)(float);
constexpr auto _func_func_plus_10__5_M  = &func_plus_10;
WRAP_FUNCTION(func_plus_10, "func_plus_10", _func_func_plus_10__5_M, _func_func_plus_10__5_M_type);

// Function: func_minus_10
// Namespace: 
using _func_func_minus_10__6_M_type = float(*)(float);
constexpr auto _func_func_minus_10__6_M  = &func_minus_10;
WRAP_FUNCTION(func_minus_10, "func_minus_10", _func_func_minus_10__6_M, _func_func_minus_10__6_M_type);

// Function: func_apply
// Namespace: 
using _func_func_apply__7_M_type = float(*)(float(*func)(float),float);
constexpr auto _func_func_apply__7_M  = &func_apply;
WRAP_FUNCTION(func_apply, "func_apply", _func_func_apply__7_M, _func_func_apply__7_M_type);

// Function: p_create
// Namespace: 
using _func_p_create__8_M_type = float *(*)();
constexpr auto _func_p_create__8_M  = &p_create;
WRAP_FUNCTION(p_create, "p_create", _func_p_create__8_M, _func_p_create__8_M_type);

// Function: p_destroy
// Namespace: 
using _func_p_destroy__9_M_type = void(*)(float *);
constexpr auto _func_p_destroy__9_M  = &p_destroy;
WRAP_FUNCTION(p_destroy, "p_destroy", _func_p_destroy__9_M, _func_p_destroy__9_M_type);

// Function: test_tuple_in
// Namespace: 
using _func_test_tuple_in__10_M_type = std::string(*)(float,float,float);
constexpr auto _func_test_tuple_in__10_M  = &test_tuple_in;
WRAP_FUNCTION(test_tuple_in, "test_tuple_in", _func_test_tuple_in__10_M, _func_test_tuple_in__10_M_type);

// Function: test_vec
// Namespace: 
using _func_test_vec__11_M_type = std::vector<std::string>(*)();
constexpr auto _func_test_vec__11_M  = &test_vec;
WRAP_FUNCTION(test_vec, "test_vec", _func_test_vec__11_M, _func_test_vec__11_M_type);

// Function: test_vec_in
// Namespace: 
using _func_test_vec_in__12_M_type = std::string(*)(std::vector<std::string>);
constexpr auto _func_test_vec_in__12_M  = &test_vec_in;
WRAP_FUNCTION(test_vec_in, "test_vec_in", _func_test_vec_in__12_M, _func_test_vec_in__12_M_type);

// Function: test_conv
// Namespace: 
using _func_test_conv__13_M_type = std::vector<std::string>(*)(std::vector<int>);
constexpr auto _func_test_conv__13_M  = &test_conv;
WRAP_FUNCTION(test_conv, "test_conv", _func_test_conv__13_M, _func_test_conv__13_M_type);

// Function: test_map
// Namespace: 
using _func_test_map__14_M_type = std::map<int, std::string>(*)();
constexpr auto _func_test_map__14_M  = &test_map;
WRAP_FUNCTION(test_map, "test_map", _func_test_map__14_M, _func_test_map__14_M_type);

// Function: test_set
// Namespace: 
using _func_test_set__15_M_type = std::set<std::string>(*)();
constexpr auto _func_test_set__15_M  = &test_set;
WRAP_FUNCTION(test_set, "test_set", _func_test_set__15_M, _func_test_set__15_M_type);

// Function: func_list
// Namespace: 
using _func_func_list__16_M_type = std::map<std::string, func_1>(*)(func_1,func_1);
constexpr auto _func_func_list__16_M  = &func_list;
WRAP_FUNCTION(func_list, "func_list", _func_func_list__16_M, _func_func_list__16_M_type);

// Function: test_map_input
// Namespace: 
using _func_test_map_input__17_M_type = std::string(*)(map_str);
constexpr auto _func_test_map_input__17_M  = &test_map_input;
WRAP_FUNCTION(test_map_input, "test_map_input", _func_test_map_input__17_M, _func_test_map_input__17_M_type);

// Class: DemoSubClass
// Namespace: 
WRAP_CLASS(DemoSubClass , "demosubclass");


using demosubclass__ref__1_M_type = long &(DemoSubClass::*)();
constexpr long &(DemoSubClass::*demosubclass__ref__1_M)()  = static_cast<long &(DemoSubClass::*)()>(&DemoSubClass::ref);
WRAP_METHOD(DemoSubClass, ref, "demosubclass.ref", demosubclass__ref__1_M, demosubclass__ref__1_M_type);

using demosubclass__vec__2_M_type = std::vector<std::string>(DemoSubClass::*)();
constexpr std::vector<std::string>(DemoSubClass::*demosubclass__vec__2_M)()  = static_cast<std::vector<std::string>(DemoSubClass::*)()>(&DemoSubClass::vec);
WRAP_METHOD(DemoSubClass, vec, "demosubclass.vec", demosubclass__vec__2_M, demosubclass__vec__2_M_type);


// Class: DemoClass
// Namespace: 
WRAP_CLASS(DemoClass , "democlass");


using democlass__set__1_M_type = void(DemoClass::*)(float);
constexpr void(DemoClass::*democlass__set__1_M)(float)  = static_cast<void(DemoClass::*)(float)>(&DemoClass::set);
WRAP_METHOD(DemoClass, set, "democlass.set", democlass__set__1_M, democlass__set__1_M_type);

using democlass__get__2_M_type = float(DemoClass::*)();
constexpr float(DemoClass::*democlass__get__2_M)()  = static_cast<float(DemoClass::*)()>(&DemoClass::get);
WRAP_METHOD(DemoClass, get, "democlass.get", democlass__get__2_M, democlass__get__2_M_type);

using democlass__sum__3_M_type = float(DemoClass::*)(float,float);
constexpr float(DemoClass::*democlass__sum__3_M)(float,float)  = static_cast<float(DemoClass::*)(float,float)>(&DemoClass::sum);
WRAP_METHOD(DemoClass, sum, "democlass.sum", democlass__sum__3_M, democlass__sum__3_M_type);

using democlass__getstring__4_M_type = std::string(DemoClass::*)();
constexpr std::string(DemoClass::*democlass__getstring__4_M)()  = static_cast<std::string(DemoClass::*)()>(&DemoClass::getString);
WRAP_METHOD(DemoClass, getString, "democlass.getstring", democlass__getstring__4_M, democlass__getstring__4_M_type);

using democlass__setstring__5_M_type = void(DemoClass::*)(std::string);
constexpr void(DemoClass::*democlass__setstring__5_M)(std::string)  = static_cast<void(DemoClass::*)(std::string)>(&DemoClass::setString);
WRAP_METHOD(DemoClass, setString, "democlass.setstring", democlass__setstring__5_M, democlass__setstring__5_M_type);

using democlass__setdemosubclass__6_M_type = void(DemoClass::*)(DemoSubClass);
constexpr void(DemoClass::*democlass__setdemosubclass__6_M)(DemoSubClass)  = static_cast<void(DemoClass::*)(DemoSubClass)>(&DemoClass::setDemoSubclass);
WRAP_METHOD(DemoClass, setDemoSubclass, "democlass.setdemosubclass", democlass__setdemosubclass__6_M, democlass__setdemosubclass__6_M_type);

using democlass__getdemosubclass__7_M_type = DemoSubClass(DemoClass::*)();
constexpr DemoSubClass(DemoClass::*democlass__getdemosubclass__7_M)()  = static_cast<DemoSubClass(DemoClass::*)()>(&DemoClass::getDemoSubclass);
WRAP_METHOD(DemoClass, getDemoSubclass, "democlass.getdemosubclass", democlass__getdemosubclass__7_M, democlass__getdemosubclass__7_M_type);

using democlass__teststatic__8_M_type = std::string(*)(int);
constexpr std::string(*democlass__teststatic__8_M)(int)  = (&DemoClass::testStatic); 
WRAP_STATIC_METHOD(DemoClass, testStatic, "democlass.teststatic", democlass__teststatic__8_M, democlass__teststatic__8_M_type);


// Class: WithConstructor
// Namespace: 
using withconstructor_1_constructor_type = void(WithConstructor::*)(float);
WRAP_CUSTOM_CLASS(WithConstructor, WithConstructor, "withconstructor.new", withconstructor_1_constructor, withconstructor_1_constructor_type);

using withconstructor__testfunc__2_M_type = float(WithConstructor::*)(float);
constexpr float(WithConstructor::*withconstructor__testfunc__2_M)(float)  = static_cast<float(WithConstructor::*)(float)>(&WithConstructor::testFunc);
WRAP_METHOD(WithConstructor, testFunc, "withconstructor.testfunc", withconstructor__testfunc__2_M, withconstructor__testfunc__2_M_type);


// Class: AfterTemplate
// Namespace: 
WRAP_CLASS(AfterTemplate , "aftertemplate");



// Class: NS::inNamespace
// Namespace: NS
WRAP_CLASS(NS::inNamespace , "ns.innamespace");


using ns_innamespace__method__1_M_type = void(NS::inNamespace::*)();
constexpr void(NS::inNamespace::*ns_innamespace__method__1_M)()  = static_cast<void(NS::inNamespace::*)()>(&NS::inNamespace::method);
WRAP_METHOD(NS::inNamespace, method, "ns.innamespace.method", ns_innamespace__method__1_M, ns_innamespace__method__1_M_type);


// Class: NS::Sub::inNestedNamespace
// Namespace: NS::Sub
WRAP_CLASS(NS::Sub::inNestedNamespace , "ns.sub.innestednamespace");


using ns_sub_innestednamespace__method__1_M_type = void(NS::Sub::inNestedNamespace::*)();
constexpr void(NS::Sub::inNestedNamespace::*ns_sub_innestednamespace__method__1_M)()  = static_cast<void(NS::Sub::inNestedNamespace::*)()>(&NS::Sub::inNestedNamespace::method);
WRAP_METHOD(NS::Sub::inNestedNamespace, method, "ns.sub.innestednamespace.method", ns_sub_innestednamespace__method__1_M, ns_sub_innestednamespace__method__1_M_type);


using nestedparent__method__1_M_type = void(NestedParent::*)();
constexpr void(NestedParent::*nestedparent__method__1_M)()  = static_cast<void(NestedParent::*)()>(&NestedParent::method);
WRAP_METHOD(NestedParent, method, "nestedparent.method", nestedparent__method__1_M, nestedparent__method__1_M_type);

// Class: NestedParent
// Namespace: 
using nestedparent_2_constructor_type = void(NestedParent::*)(float);
WRAP_CUSTOM_CLASS(NestedParent, NestedParent, "nestedparent.new", nestedparent_2_constructor, nestedparent_2_constructor_type);


using _nestedparent_nestedparent_nestedstruct__method__1_M_type = void(::NestedParent::NestedParent::NestedStruct::*)();
constexpr void(::NestedParent::NestedParent::NestedStruct::*_nestedparent_nestedparent_nestedstruct__method__1_M)()  = static_cast<void(::NestedParent::NestedParent::NestedStruct::*)()>(&::NestedParent::NestedParent::NestedStruct::method);
WRAP_METHOD(::NestedParent::NestedParent::NestedStruct, method, ".nestedparent.nestedparent.nestedstruct.method", _nestedparent_nestedparent_nestedstruct__method__1_M, _nestedparent_nestedparent_nestedstruct__method__1_M_type);

// Class: ::NestedParent::NestedParent::NestedStruct
// Namespace: ::NestedParent
using _nestedparent_nestedparent_nestedstruct_2_constructor_type = void(::NestedParent::NestedParent::NestedStruct::*)(float);
WRAP_CUSTOM_CLASS(::NestedParent::NestedParent::NestedStruct, NestedParent::NestedStruct, ".nestedparent.nestedparent.nestedstruct.new", _nestedparent_nestedparent_nestedstruct_2_constructor, _nestedparent_nestedparent_nestedstruct_2_constructor_type);


// Class: SameName::SameName
// Namespace: SameName
WRAP_CLASS(SameName::SameName , "samename.samename");


using samename_samename__method__1_M_type = void(SameName::SameName::*)();
constexpr void(SameName::SameName::*samename_samename__method__1_M)()  = static_cast<void(SameName::SameName::*)()>(&SameName::SameName::method);
WRAP_METHOD(SameName::SameName, method, "samename.samename.method", samename_samename__method__1_M, samename_samename__method__1_M_type);


// Class: SameName::SameName::SameName::NestedStructNS
// Namespace: SameName::SameName
WRAP_CLASS(SameName::SameName::SameName::NestedStructNS , "samename.samename.samename.nestedstructns");


using samename_samename_samename_nestedstructns__method__1_M_type = void(SameName::SameName::SameName::NestedStructNS::*)();
constexpr void(SameName::SameName::SameName::NestedStructNS::*samename_samename_samename_nestedstructns__method__1_M)()  = static_cast<void(SameName::SameName::SameName::NestedStructNS::*)()>(&SameName::SameName::SameName::NestedStructNS::method);
WRAP_METHOD(SameName::SameName::SameName::NestedStructNS, method, "samename.samename.samename.nestedstructns.method", samename_samename_samename_nestedstructns__method__1_M, samename_samename_samename_nestedstructns__method__1_M_type);


// Class: BaseClass
// Namespace: 
WRAP_CLASS(BaseClass , "baseclass");


using baseclass__v__1_M_type = std::string(BaseClass::*)();
constexpr std::string(BaseClass::*baseclass__v__1_M)()  = static_cast<std::string(BaseClass::*)()>(&BaseClass::v);
WRAP_METHOD(BaseClass, v, "baseclass.v", baseclass__v__1_M, baseclass__v__1_M_type);


// Class: DerivedClass
// Namespace: 
WRAP_CLASS(DerivedClass , "derivedclass");


using derivedclass__v__1_M_type = std::string(DerivedClass::*)();
constexpr std::string(DerivedClass::*derivedclass__v__1_M)()  = static_cast<std::string(DerivedClass::*)()>(&DerivedClass::v);
WRAP_METHOD(DerivedClass, v, "derivedclass.v", derivedclass__v__1_M, derivedclass__v__1_M_type);


// Class: PolyValue
// Namespace: 
WRAP_CLASS(PolyValue , "polyvalue");


using polyvalue__setvalue__1_M_type = void(PolyValue::*)(BaseClass *);
constexpr void(PolyValue::*polyvalue__setvalue__1_M)(BaseClass *)  = static_cast<void(PolyValue::*)(BaseClass *)>(&PolyValue::setValue);
WRAP_METHOD(PolyValue, setValue, "polyvalue.setvalue", polyvalue__setvalue__1_M, polyvalue__setvalue__1_M_type);

using polyvalue__valueptr__2_M_type = BaseClass *(PolyValue::*)();
constexpr BaseClass *(PolyValue::*polyvalue__valueptr__2_M)()  = static_cast<BaseClass *(PolyValue::*)()>(&PolyValue::valuePtr);
WRAP_METHOD(PolyValue, valuePtr, "polyvalue.valueptr", polyvalue__valueptr__2_M, polyvalue__valueptr__2_M_type);

using polyvalue__value__3_M_type = BaseClass(PolyValue::*)();
constexpr BaseClass(PolyValue::*polyvalue__value__3_M)()  = static_cast<BaseClass(PolyValue::*)()>(&PolyValue::value);
WRAP_METHOD(PolyValue, value, "polyvalue.value", polyvalue__value__3_M, polyvalue__value__3_M_type);

}
}