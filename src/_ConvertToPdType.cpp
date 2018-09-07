#include "_Converters.hpp"



// OLD

template <>
Atom TypedAtomT<float>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<double>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<int>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<long>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<std::string>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(gensym(_d.data()->value->c_str()));
}

// ---
// TODO: use references?
template <>
Atom TypedAtomT<float&>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<double&>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<int&>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<long&>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(*_d.data()->value);
}

template <>
Atom TypedAtomT<std::string&>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(gensym(_d.data()->value->c_str()));
}

template <>
Atom TypedAtomT<const char*>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(gensym(*_d.data()->value));
}


template <>
Atom TypedAtomT<char*>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(gensym(*_d.data()->value));
}
