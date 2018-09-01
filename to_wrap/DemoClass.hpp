#include <string>
#include <vector>

class DemoSubClass{
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

    static void testStatic(int i){};
};

// currently this doesn't work:

class WithConstructor
{
public:
    explicit WithConstructor(float f)
    {}
    
    template <typename T>
    void shouldBeSkipped(){}
};

//
//template<typename T>
//class ShouldBeSkipped
//{};
//
//template<>
//class ShouldBeSkipped<void>{};


