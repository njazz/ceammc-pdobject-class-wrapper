#include "_Converters.hpp"

// 1. atoms
template <>
void toAtomList(AtomList& out, float v) { out = AtomList(Atom(v)); }

template <>
void toAtomList(AtomList& out, double v) { out = AtomList(Atom(v)); }

template <>
void toAtomList(AtomList& out, std::string v) { out = AtomList(Atom(gensym(v.c_str()))); }

template <>
void toAtomList(AtomList& out, int v) { out = AtomList(Atom(v)); }

template <>
void toAtomList(AtomList& out, long v) { out = AtomList(Atom(v)); }

template <>
void toAtomList(AtomList& out, const char* v) { out = AtomList(Atom(gensym(v))); }

template <>
void toAtomList(AtomList& out, char* v) { out = AtomList(Atom(gensym(v))); }

// 2. lists

template <>
void toAtomList(AtomList& out, std::vector<std::string> v) {
    AtomList ret;
    for (auto e : v)
    {
        ret.append(Atom(gensym(e.c_str())));
    }
    out = ret;
}

// ===

// OLD

//template <>
//Atom TypedAtomT<float>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<double>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<int>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<long>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<std::string>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(gensym(_d.data()->value->c_str()));
//}

//// ---
//// TODO: use references?
//template <>
//Atom TypedAtomT<float&>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<double&>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<int&>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<long&>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(*_d.data()->value);
//}

//template <>
//Atom TypedAtomT<std::string&>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(gensym(_d.data()->value->c_str()));
//}

//template <>
//Atom TypedAtomT<const char*>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(gensym(*_d.data()->value));
//}

//template <>
//Atom TypedAtomT<char*>::asAtom()
//{
//    if (!_d.data())
//        return Atom(gensym("<empty>"));

//    return Atom(gensym(*_d.data()->value));
//}