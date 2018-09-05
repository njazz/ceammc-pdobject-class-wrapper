#include "DemoClass.hpp"

long& DemoSubClass::ref(){return _v;}
std::vector<std::string> DemoSubClass::vec(){return {"lol"};}

float test_function_wrapper(void* ptr)
{
    return -42.0f;
}
