#include "DemoClass.hpp"

#include "m_pd.h"

long& DemoSubClass::ref() { return _v; }
std::vector<std::string> DemoSubClass::vec() { return { "lol" }; }

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

void test_function_wrapper_v(void* ptr) {}
void test_function_wrapper_v_ptr(float (*ptr)(float)) {}
void test_function_wrapper_v_ptr_v(void (*ptr)(float)) {}

// ---
float* p_create()
{
    auto ret = new float;
    post("create ptr %lu", (long)ret);
    return ret;
}
void p_destroy(float* p)
{
    post("would destroy ptr %lu", (long)p);
    //   if (p) delete p;
}

// ---

std::string test_tuple_in(float a, float b, float c)
{
    return "test: " + std::to_string(a) + " , " + std::to_string(b) + " , " + std::to_string(c);
}

std::vector<std::string> test_vec()
{
    return { "demo", "vector", "abcde", "123" };
}

std::string test_vec_in(std::vector<std::string> v)
{
    std::string ret = " ** ";
    for (auto e : v) {
        ret = ret + e + " ** ";
    }
    return ret;
}

std::vector<std::string> test_conv(std::vector<int> v)
{
    std::vector<std::string> ret;
    for (auto e : v) {
        ret.push_back(std::to_string(e));
    }
    return ret;
}

//
std::map<int, std::string> test_map()
{
    return { { 1, "key one" }, { 42, "the question" } };
}

std::set<std::string> test_set()
{
    return { "ordered", "set", "with", "strings" };
}

//
std::map<std::string, func_1> func_list(func_1 a, func_1 b)
{
    std::map<std::string, func_1> ret;
    ret["A"] = [](float v) -> float { return -1; }; //a;
    ret["B"] = [](float v) -> float { return 3; }; //b;
    return ret;
}

//func_1 func_l_plus_10()
//{
//    return [](float v) { return v + 10; };
//}
//func_1 func_l_minus_10()
//{
//    return [](float v) { return v - 10; };
//}
//float func_l_apply(func_1 f = [](float)->float{return 0;}, float v=0)
//{
//    return f(v);
//}

// testing this:
#include "ceammc_atomlist.h"
#include "ceammc_data.h"
#include "datatype_dict.h"

#include "_Converters.hpp"

using namespace ceammc;

template <>
void _toAtomList(AtomList& out, std::map<std::string, func_1> v)
{
    AtomList ret;

    auto s1 = new DataTypeDict();

    for (auto e : v) {
        AtomList tmp;
        _toAtomList(tmp, e.second);
        s1->insert(Atom(gensym(e.first.c_str())), tmp);
    }

    post("template converter");

    // TODO needs to be fixed:
    auto ptr = new DataTPtr<DataTypeDict>(s1);
    auto da = DataAtom(*ptr);
    ret = AtomList(da.toAtom());

    ret.at(0).isData();
    auto d_o = DataAtom(ret.at(0));

    out = ret;
}
