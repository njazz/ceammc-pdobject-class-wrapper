#include "ClassWrapper.hpp"
#include "DemoClass.hpp"

extern "C"{
void setup(){

// DemoClass.hpp

// Class: DemoSubClass
//
WRAP_CLASS(DemoSubClass , "demo-sub-class");
using _MDemoSubClass__ref__0_type = long &(DemoSubClass::*const)();
constexpr long &(DemoSubClass::*_MDemoSubClass__ref__0)()  = static_cast<long &(DemoSubClass::*)()>(&DemoSubClass::ref);
WRAP_METHOD(DemoSubClass , ref , "demo-sub-class.ref",_MDemoSubClass__ref__0,_MDemoSubClass__ref__0_type);

using _MDemoSubClass__vec__1_type = std::vector<std::string>(DemoSubClass::*const)();
constexpr std::vector<std::string>(DemoSubClass::*_MDemoSubClass__vec__1)()  = static_cast<std::vector<std::string>(DemoSubClass::*)()>(&DemoSubClass::vec);
WRAP_METHOD(DemoSubClass , vec , "demo-sub-class.vec",_MDemoSubClass__vec__1,_MDemoSubClass__vec__1_type);



// Class: DemoClass
//
WRAP_CLASS(DemoClass , "demo-class");
using _MDemoClass__set__0_type = void(DemoClass::*const)(float);
constexpr void(DemoClass::*_MDemoClass__set__0)(float)  = static_cast<void(DemoClass::*)(float)>(&DemoClass::set);
WRAP_METHOD(DemoClass , set , "demo-class.set",_MDemoClass__set__0,_MDemoClass__set__0_type);

using _MDemoClass__get__1_type = float(DemoClass::*const)();
constexpr float(DemoClass::*_MDemoClass__get__1)()  = static_cast<float(DemoClass::*)()>(&DemoClass::get);
WRAP_METHOD(DemoClass , get , "demo-class.get",_MDemoClass__get__1,_MDemoClass__get__1_type);

using _MDemoClass__sum__2_type = float(DemoClass::*const)(float,float);
constexpr float(DemoClass::*_MDemoClass__sum__2)(float,float)  = static_cast<float(DemoClass::*)(float,float)>(&DemoClass::sum);
WRAP_METHOD(DemoClass , sum , "demo-class.sum",_MDemoClass__sum__2,_MDemoClass__sum__2_type);

using _MDemoClass__getString__3_type = std::string(DemoClass::*const)();
constexpr std::string(DemoClass::*_MDemoClass__getString__3)()  = static_cast<std::string(DemoClass::*)()>(&DemoClass::getString);
WRAP_METHOD(DemoClass , getString , "demo-class.getstring",_MDemoClass__getString__3,_MDemoClass__getString__3_type);

using _MDemoClass__setString__4_type = void(DemoClass::*const)(std::string);
constexpr void(DemoClass::*_MDemoClass__setString__4)(std::string)  = static_cast<void(DemoClass::*)(std::string)>(&DemoClass::setString);
WRAP_METHOD(DemoClass , setString , "demo-class.setstring",_MDemoClass__setString__4,_MDemoClass__setString__4_type);

using _MDemoClass__setDemoSubclass__5_type = void(DemoClass::*const)(DemoSubClass);
constexpr void(DemoClass::*_MDemoClass__setDemoSubclass__5)(DemoSubClass)  = static_cast<void(DemoClass::*)(DemoSubClass)>(&DemoClass::setDemoSubclass);
WRAP_METHOD(DemoClass , setDemoSubclass , "demo-class.setdemosubclass",_MDemoClass__setDemoSubclass__5,_MDemoClass__setDemoSubclass__5_type);

using _MDemoClass__getDemoSubclass__6_type = DemoSubClass(DemoClass::*const)();
constexpr DemoSubClass(DemoClass::*_MDemoClass__getDemoSubclass__6)()  = static_cast<DemoSubClass(DemoClass::*)()>(&DemoClass::getDemoSubclass);
WRAP_METHOD(DemoClass , getDemoSubclass , "demo-class.getdemosubclass",_MDemoClass__getDemoSubclass__6,_MDemoClass__getDemoSubclass__6_type);


}
}