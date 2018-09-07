// converters

#ifndef _Converters_hpp
#define _Converters_hpp

#include "_AbstractDataWrapT.hpp"
#include "ceammc_atomlist.h"
#include "ceammc_dataatom.h"

template <typename T>
class TypedAtomT : public Atom {
    DataTPtr<AbstractDataWrapT<T> > _d;

public:
    explicit TypedAtomT(T v)
        : _d(new AbstractDataWrapT<T>(v))
    {
    }

    virtual ~TypedAtomT()
    {
        _d = 0;
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


// ====================
// NEW HEADERS

template <typename T>
int fromAtomList(T& out, AtomList l);

template <typename T>
int fromAtomList(T& out, AtomList l)
{
    auto a = l.last();//at(0);
    if (DataAtom(*a).isData()) {
        auto da = DataAtom(*a);
        auto o_ = da.data().as<AbstractDataWrapT<T> >();
        out = *o_->value;


    }
    return 1;
};

template <typename T>
void toAtomList(AtomList& out, T v);


#endif
