#include "_Converters.hpp"

// 1. atoms
template <>
void _toAtomList(AtomList& out, float v) { out = AtomList(Atom(v)); }

template <>
void _toAtomList(AtomList& out, double v) { out = AtomList(Atom(v)); }

template <>
void _toAtomList(AtomList& out, std::string v) { out = AtomList(Atom(gensym(v.c_str()))); }

template <>
void _toAtomList(AtomList& out, int v) { out = AtomList(Atom(v)); }

template <>
void _toAtomList(AtomList& out, long v) { out = AtomList(Atom(v)); }

template <>
void _toAtomList(AtomList& out, const char* v) { out = AtomList(Atom(gensym(v))); }

template <>
void _toAtomList(AtomList& out, char* v) { out = AtomList(Atom(gensym(v))); }

// 2. lists

template <>
void _toAtomList(AtomList& out, std::vector<std::string> v)
{
    AtomList ret;
    for (auto e : v) {
        ret.append(Atom(gensym(e.c_str())));
    }
    out = ret;
}

template <>
void _toAtomList(AtomList& out, std::vector<int> v)
{
    AtomList ret;
    for (auto e : v) {
        ret.append(Atom(e));
    }
    out = ret;
}

template <>
void _toAtomList(AtomList& out, std::vector<float> v)
{
    AtomList ret;
    for (auto e : v) {
        ret.append(Atom(e));
    }
    out = ret;
}

template <>
void _toAtomList(AtomList& out, std::vector<long> v)
{
    AtomList ret;
    for (auto e : v) {
        ret.append(Atom(e));
    }
    out = ret;
}

template <>
void _toAtomList(AtomList& out, std::vector<double> v)
{
    AtomList ret;
    for (auto e : v) {
        ret.append(Atom(e));
    }
    out = ret;
}

