// converts AtomList <-> tuple

#ifndef AtomListWrapperT_hpp
#define AtomListWrapperT_hpp

#include "_AbstractDataWrapT.hpp"
#include "_SequenceT.hpp"
#include "_functionTraits.hpp"

#include "ceammc_atomlist.h"

//#include "ceammc_abstractdata.h"

#include "ceammc_data.h"
//#include "ceammc_dataatom.h"
//#include "ceammc_object.h"

//#include <functional>

//#include "TypeConstructor.hpp"

template <typename T>
class TypedAtomT : public Atom {
    DataTPtr<AbstractDataWrapT<T> > _d; //= DataTPtr<T>(Atom()) ;

public:
    TypedAtomT(T v)
        : _d(new AbstractDataWrapT<T>(v))
    {
    }

    TypedAtomT()
        : _d(new AbstractDataWrapT<T>())
    {
    }

    Atom asAtom()
    {
        return _d.toAtom();
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

    return Atom(_d.data()->value);
}

template <>
Atom TypedAtomT<std::string>::asAtom()
{
    if (!_d.data())
        return Atom(gensym("<empty>"));

    return Atom(gensym(_d.data()->value.c_str()));
}

// ---------------------

// --

template <typename T>
void convertAtom(T& out, Atom a);

template <>
void convertAtom(float& out, Atom a) { out = a.asFloat(); }

template <>
void convertAtom(std::string& out, Atom a) { out = a.asString(); }

template <>
void convertAtom(int& out, Atom a) { out = a.asInt(); }

// -----

template <int I, typename T>
class _tupleFromAtomlistT {
public:
    T& output;

    _tupleFromAtomlistT(T& o)
        : output(o)
    {
    }

    void operator()(const AtomList& src)
    {
        //std::tuple_element<I, T> el;
        using el_type = decltype(std::get<I - 1>(output));

        auto& el = std::get<I - 1>(output);
        auto atom = src.at(I - 1);

        // el_type value = convertAtom<el_type>(atom);
        // std::get<I - 1>(output) = value;

        convertAtom(el, atom);

        AtomList next = src;
        next.remove(0);

        tail(next);
    }

    _tupleFromAtomlistT<I - 1, T> tail = _tupleFromAtomlistT<I - 1, T>(output);
};

template <typename T>
class _tupleFromAtomlistT<0, T> {
public:
    T& output;

    _tupleFromAtomlistT(T& o)
        : output(o)
    {
    }
    void operator()(const AtomList& src) {}
};

// ---

template <typename F>
class AtomListWrapperT : public AtomList {
    using Traits = _functionTraits<F>;

public:
    typename Traits::arguments output;
    bool validOutput = false;

    AtomListWrapperT(const AtomList& src)
    {
        constexpr size_t tupleSize = std::tuple_size<typename Traits::arguments>::value;
        if (src.size() != tupleSize) {
            return;
        }

        _tupleFromAtomlistT<tupleSize, typename Traits::arguments> proc(output);
        proc(src);
        validOutput = true;
    };
};

#endif
