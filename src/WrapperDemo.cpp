#include "ClassWrapper.hpp"

#include "DemoClass.hpp"

extern "C" {
void setup()
{
    WRAP_CLASS(DemoClass, "demo.float");
    WRAP_CLASS(DemoSubClass, "demo.subclass");

    WRAP_METHOD(DemoClass, get, "demo.float.get");
    WRAP_METHOD(DemoClass, set, "demo.float.set");

    WRAP_METHOD(DemoClass, sum, "demo.float.sum");

    WRAP_METHOD(DemoClass, getString, "demo.float.getstring");
    WRAP_METHOD(DemoClass, setString, "demo.float.setstring");

    WRAP_METHOD(DemoClass, getDemoSubclass, "demo.float.getsubclass");
    WRAP_METHOD(DemoClass, setDemoSubclass, "demo.float.setsubclass");

    WRAP_METHOD(DemoSubClass, ref, "demo.subclass.ref");

}
}
