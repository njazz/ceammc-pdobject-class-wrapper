#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "_AtomListWrapperT.hpp"

#include <iostream>

#include "ceammc_data.h"

template <typename T>
void _func1(T value1){};

template <typename T>
void _tester(T v)
{
    ArgumentsFromAtomList<decltype(_func1<T>)> aw((AtomList(Atom(v))));
    REQUIRE(std::get<0>(aw.output) == v);

    std::cout << "tested: " << typeid(T).name() << "\n";
}

template <typename T>
void _tester_dataPtr(T v)
{
    DataTPtr< ArgumentsFromAtomList<decltype(_func1<T>)> > dtptr;
    ArgumentsFromAtomList<decltype(_func1<T>)> aw((AtomList(Atom(v))));
    dtptr = (&aw);

    REQUIRE(std::get<0>(aw.output) == v);

    std::cout << "tested: " << typeid(T).name() << "\n";
}



TEST_CASE("_AtomListWrapperT", "wrapper")
{
    SECTION("1. basic")
    {
        _tester(1);
        _tester(.2f);
        // double loses precision:
        //        _tester(.3);

        // symbol crashes (pd init)
        //        _tester(gensym("string"));
    }
}
