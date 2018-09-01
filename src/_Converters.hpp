// converters

template <typename T>
class TypedAtomT : public Atom {
    DataTPtr<AbstractDataWrapT<T> > _d;

public:
    explicit TypedAtomT(T v)
        : _d(new AbstractDataWrapT<T>(v))
    {
    }

    TypedAtomT()
        : _d(new AbstractDataWrapT<T>())
    {
    }

    Atom asAtom()
    {
        return DataAtom(_d).toAtom();
    }
};

template <>
class TypedAtomT<void> : public Atom {
public:
    TypedAtomT(void* v = 0) {}
    Atom asAtom() { return Atom(); }
};

//---

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
