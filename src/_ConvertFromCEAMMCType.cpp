#include "_Converters.hpp"

#include <set>

#include "datatype_dict.h"

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

// 2. Dicts

// STUB

using namespace ceammc;

template <>
int _fromAtomList(std::map<std::string, std::string>& out, AtomList l)
{
    auto d = DataAtom(l.at(0)).as<DataTypeDict>();

    if (!d)
        return 1;

    for (auto k : d->innerData()) {
        if (d->valueT<Atom>(k.first))
            out[k.first.asString()] = d->valueT<Atom>(k.first)->asString();
    }

    return 1;
}
