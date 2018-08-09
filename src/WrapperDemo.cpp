#include "TypeWrapper.hpp"

#include <string>

class DemoSubClass{
    long _v = 123;
public:
    long& ref(){return _v;}
};

class DemoClass {
    float _data = 42.0f;
    std::string _string = "fourty-two";
    DemoSubClass _subClass;

public:
    void set(float f)
    {
        _data = f;
    };

    float get()
    {
        return _data;
    };

    float sum(float a, float b)
    {
        return a+b;
    }

    std::string getString() {return _string;}

    void setString(std::string s) {_string =s;}

    void setDemoSubclass(DemoSubClass c)
    {
        _subClass = c;
    }
    DemoSubClass getDemoSubclass()
    {
        return _subClass;
    }
};

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
