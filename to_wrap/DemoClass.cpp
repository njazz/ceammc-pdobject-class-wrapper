#include "DemoClass.hpp"

/*

long& DemoSubClass::ref() { return _v; }
std::vector<std::string> DemoSubClass::vec() { return { "lol" }; }

*/

float test_function_wrapper(void* ptr)
{
    return -42.0f;
}

#define MACRO_1 float
MACRO_1 test_macro1()
{
    return 42.0f;
}

float func_plus_10(float v)
{
    return v + 10;
}
float func_minus_10(float v)
{
    return v - 10;
}
float func_apply(float (*func)(float), float v)
{
    if (func)
        return (*func)(v);
    return 0;
}

// --

void test_function_wrapper_v(void* ptr){}
void test_function_wrapper_v_ptr(float (*ptr)(float)){}
void test_function_wrapper_v_ptr_v(void (*ptr)(float)){}
