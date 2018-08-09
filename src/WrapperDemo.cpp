#include "TypeWrapper.hpp"

#include <string>

class DemoClass {
    float _data = 42.0f;
    std::string _string = "fourty-two";

public:
    void set(float f)
    {
        _data = f;
    };

    float get()
    {
        return _data;
    };

    std::string getString() {return _string;}

    void setString(std::string s) {_string =s;}
};

extern "C" {
void setup()
{
    WRAP_CLASS(DemoClass, "demo.float");
    WRAP_METHOD(DemoClass, get, "demo.float.get");
    WRAP_METHOD(DemoClass, set, "demo.float.set");

    WRAP_METHOD(DemoClass, getString, "demo.float.getstring");
    WRAP_METHOD(DemoClass, setString, "demo.float.setstring");
}
}
