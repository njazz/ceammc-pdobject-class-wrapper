#include "_Converters.hpp"

// 1. atoms

template <>
int _fromAtomList(float& out, AtomList l)
{
    out = l.last()->asFloat();
    return 1;
}

template <>
int _fromAtomList(double& out, AtomList l)
{
    out = l.last()->asFloat();
    return 1;
}

template <>
int _fromAtomList(std::string& out, AtomList l)
{
    out = l.last()->asString();
    return 1;
}

template <>
int _fromAtomList(int& out, AtomList l)
{
    out = l.last()->asInt();
    return 1;
}

template <>
int _fromAtomList(long& out, AtomList l)
{
    out = l.last()->asInt();
    return 1;
}

template <>
int _fromAtomList(const char*& out, AtomList l)
{
    out = l.last()->asSymbol()->s_name;
    return 1;
}

template <>
int _fromAtomList(char*& out, AtomList l)
{
    out = l.last()->asSymbol()->s_name;
    return 1;
}

// 2. lists

template <>
int _fromAtomList(std::vector<std::string>& out, AtomList l)
{
    for (auto& e : l) {
        out.push_back(e.asSymbol()->s_name);
    }

    return l.size();
}

template <>
int _fromAtomList(std::vector<int>& out, AtomList l)
{
    for (auto& e : l) {
        out.push_back(e.asInt());
    }

    return l.size();
}

template <>
int _fromAtomList(std::vector<long>& out, AtomList l)
{
    for (auto& e : l) {
        out.push_back(e.asInt());
    }

    return l.size();
}

template <>
int _fromAtomList(std::vector<float>& out, AtomList l)
{
    for (auto& e : l) {
        out.push_back(e.asFloat());
    }

    return l.size();
}

template <>
int _fromAtomList(std::vector<double>& out, AtomList l)
{
    for (auto& e : l) {
        out.push_back(e.asFloat());
    }

    return l.size();
}
