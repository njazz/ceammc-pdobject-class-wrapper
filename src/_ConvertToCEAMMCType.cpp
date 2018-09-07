#include "_Converters.hpp"

#include "datatype_dict.h"
#include "datatype_set.h"
#include "datatype_string.h"

#include "m_pd.h"

// ===============================
// 1. sets

template <>
void _toAtomList(AtomList& out, std::set<std::string> v)
{
    AtomList ret;

    auto s1 = new DataTypeSet();
    for (auto e : v) {
        s1->add(Atom(gensym(e.c_str())));
    }

    // TODO needs to be fixed:
    auto ptr = new DataTPtr<DataTypeSet>(s1);
    auto da = DataAtom(*ptr);
    ret = AtomList(da.toAtom());

    out = ret;
}

template <>
void _toAtomList(AtomList& out, std::set<float> v)
{
    AtomList ret;

    auto s1 = new DataTypeSet();
    for (auto e : v) {
        s1->add(Atom(e));
    }

    // TODO needs to be fixed:
    auto ptr = new DataTPtr<DataTypeSet>(s1);
    auto da = DataAtom(*ptr);
    ret = AtomList(da.toAtom());

    out = ret;
}

// ===============================
// 2. dict

template <>
void _toAtomList(AtomList& out, std::map<int, std::string> v)
{
    AtomList ret;

    auto s1 = new DataTypeDict();

    for (auto e : v) {
        s1->insert(std::to_string(e.first), e.second);
    }

    // TODO needs to be fixed:
    auto ptr = new DataTPtr<DataTypeDict>(s1);
    auto da = DataAtom(*ptr);
    ret = AtomList(da.toAtom());

    ret.at(0).isData();
    auto d_o = DataAtom(ret.at(0));

    out = ret;
}

template <>
void _toAtomList(AtomList& out, std::map<std::string, std::string> v)
{
    AtomList ret;

    auto s1 = new DataTypeDict();

    for (auto e : v) {
        s1->insert(e.first, e.second);
    }

    // TODO needs to be fixed:
    auto ptr = new DataTPtr<DataTypeDict>(s1);
    auto da = DataAtom(*ptr);
    ret = AtomList(da.toAtom());

    ret.at(0).isData();
    auto d_o = DataAtom(ret.at(0));

    out = ret;
}

template <>
void _toAtomList(AtomList& out, std::map<std::string, float> v)
{
    AtomList ret;

    auto s1 = new DataTypeDict();

    for (auto e : v) {
        s1->insert(e.first, std::to_string(e.second));
    }

    // TODO needs to be fixed:
    auto ptr = new DataTPtr<DataTypeDict>(s1);
    auto da = DataAtom(*ptr);
    ret = AtomList(da.toAtom());

    ret.at(0).isData();
    auto d_o = DataAtom(ret.at(0));

    out = ret;
}

//template <typename U>
//void _toAtomList(AtomList& out, std::map<std::string, U> v)
//{
//    AtomList ret;

//    auto s1 = new DataTypeDict();

//    for (auto e : v) {
//        AtomList tmp;
//        _toAtomList(tmp, e.second);
//        s1->insert(e.first, tmp);
//    }

//    post("template converter");

//    // TODO needs to be fixed:
//    auto ptr = new DataTPtr<DataTypeDict>(s1);
//    auto da = DataAtom(*ptr);
//    ret = AtomList(da.toAtom());

//    ret.at(0).isData();
//    auto d_o = DataAtom(ret.at(0));

//    out = ret;
//}
