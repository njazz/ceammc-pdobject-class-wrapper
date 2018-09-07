#include "_Converters.hpp"

#include <set>

// 1. Sets

template <>
int _fromAtomList(std::set<float>& out, AtomList l)
{
    for (auto& e : l) {
        out.insert(e.asFloat());
    }

    return l.size();
}

template <>
int _fromAtomList(std::set<double>& out, AtomList l)
{
    for (auto& e : l) {
        out.insert(e.asFloat());
    }

    return l.size();
}

template <>
int _fromAtomList(std::set<int>& out, AtomList l)
{
    for (auto& e : l) {
        out.insert(e.asFloat());
    }

    return l.size();
}

template <>
int _fromAtomList(std::set<long>& out, AtomList l)
{
    for (auto& e : l) {
        out.insert(e.asFloat());
    }

    return l.size();
}

template <>
int _fromAtomList(std::set<std::string>& out, AtomList l)
{
    for (auto& e : l) {
        out.insert(e.asString());
    }

    return l.size();
}
