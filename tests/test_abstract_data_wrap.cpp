#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "_AbstractDataWrapT.hpp"

#include <iostream>

#include <vector>
#include <set>
#include <map>
#include <array>

template <typename T>
void _tester(T v)
{
    AbstractDataWrapT<T> df;

    *df.value = v;
    REQUIRE(df.type() == AbstractDataWrapT<T>::dataType);

    auto dfc = df.clone();

    REQUIRE(*dfc->template as<AbstractDataWrapT<T> >()->value == v);
    REQUIRE(dfc->type() == AbstractDataWrapT<T>::dataType);

    delete dfc;
    REQUIRE(1);

    std::cout << "typename: " << df.toString() << " [" << typeid(T).name() << "]"
              << " (" << df.type() << ")\n";
}

TEST_CASE("_AbstractDataWrapT", "wrapper")
{
    SECTION("1. basic types")
    {
        _tester(.33f);
        _tester(.33);
        _tester(3);
    }

    SECTION("2. containers")
    {
        _tester(std::vector<int>({1,2,3}));
        _tester(std::vector<float>({.1,.2,.3}));
        _tester(std::vector<std::string>({"1","2","3"}));
    }
}
