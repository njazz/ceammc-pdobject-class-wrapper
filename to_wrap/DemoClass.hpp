#include <string>
#include <vector>

class DemoSubClass {
    long _v = 123;

public:
    long& ref();
    std::vector<std::string> vec();
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
        return a + b;
    }

    std::string getString() { return _string; }
    void setString(std::string s) { _string = s; }

    void setDemoSubclass(DemoSubClass c)
    {
        _subClass = c;
    }

    DemoSubClass getDemoSubclass()
    {
        return _subClass;
    }

    static std::string testStatic(int i) { return std::string("result: ") + std::to_string(i); };
};

class WithConstructor {
    float _val = 0;

public:
    explicit WithConstructor(float f)
        : _val(f)
    {
    }

    template <typename T>
    void shouldBeSkipped() {}

    float testFunc(float input) { return 100 * _val * input; }
};

template <typename T>
class ShouldBeSkipped {
};

//
template <>
class ShouldBeSkipped<void> {
};

class AfterTemplate : public ShouldBeSkipped<void> {
};



namespace NS {
class inNamespace {
public:
    void method(){};
};
namespace Sub {
    class inNestedNamespace {
    public:
        void method(){};
    };
}
}

// ---
struct NestedParent
{
    void method(){};
    NestedParent(float f){};

    struct NestedStruct{
        void method(){};
        NestedStruct(float f){};

    };
};

namespace SameName {
struct SameName
{
    void method(){};

    struct NestedStructNS{
        void method(){};
    };
};

}

// ---

// not working: unions in class/struct
//class ClassWithUnion
//{
//public:
//    union {float f; int i;} ;
//};

// not working: variadic functions
//class VariadicFunc
//{
//public:
//    void var(float f,...){};
//};

