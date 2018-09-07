// converters

#ifndef _Converters_hpp
#define _Converters_hpp

#include "_AbstractDataWrapT.hpp"
#include "ceammc_atomlist.h"
#include "ceammc_dataatom.h"

#include "m_pd.h"

template <typename T>
int _fromAtomList(T& out, AtomList l);

template <typename T>
void _toAtomList(AtomList& out, T v);

// ---

template <typename T>
class AtomListFromReturnType { //: public Atom {
    DataTPtr<AbstractDataWrapT<T> > _d;

public:
    explicit AtomListFromReturnType(T v)
        : _d(new AbstractDataWrapT<T>(v))
    {
    }

    virtual ~AtomListFromReturnType()
    {
        _d = 0;
    }

    AtomListFromReturnType()
        : _d(new AbstractDataWrapT<T>())
    {
    }

    AtomList asAtomList()
    {
        AtomList ret;

        if (!_d.data())
            return AtomList(Atom(gensym("<empty>")));

        _toAtomList(ret, *_d.data()->value);

        return ret;
    }
};

template <>
class AtomListFromReturnType<void> : public Atom {
public:
    AtomListFromReturnType(void* v = 0) {}
    AtomList asAtomList()
    {
        AtomList ret;
        return ret;
    }
};

//---

// ====================
// NEW HEADERS

template <typename T>
int _fromAtomList(T& out, AtomList l)
{
    auto a = l.last(); //at(0);
    if (DataAtom(*a).isData()) {
        auto da = DataAtom(*a);
        auto o_ = da.data().as<AbstractDataWrapT<T> >();
        out = *o_->value;
    }
    return 1;
};

template <typename T>
void _toAtomList(AtomList& out, T v)
{
    auto d = new AbstractDataWrapT<T>(v);
    out = AtomList(DataAtom(d).toAtom());
}

#endif
