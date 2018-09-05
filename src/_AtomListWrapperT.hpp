// converts AtomList <-> tuple

#ifndef AtomListWrapperT_hpp
#define AtomListWrapperT_hpp

#include "_AbstractDataWrapT.hpp"
#include "_SequenceT.hpp"
#include "_FunctionTraits.hpp"

#include "ceammc_atomlist.h"
#include "ceammc_data.h"
#include "ceammc_dataatom.h"

#include "_Converters.hpp"

// ---------------------

template <typename T>
void convertAtom(T& out, Atom a)
{
    if (DataAtom(a).isData()) {
        auto da = DataAtom(a);
        auto o_ = da.data().as<AbstractDataWrapT<T> >();
        out = *o_->value;
    }
};

template <>
void convertAtom(float& out, Atom a) { out = a.asFloat(); }

template <>
void convertAtom(double& out, Atom a) { out = a.asFloat(); }

template <>
void convertAtom(std::string& out, Atom a) { out = a.asString(); }

template <>
void convertAtom(int& out, Atom a) { out = a.asInt(); }

template <>
void convertAtom(long& out, Atom a) { out = a.asInt(); }

template <>
void convertAtom(const char*& out, Atom a) { out = a.asSymbol()->s_name; }

template <>
void convertAtom(char*& out, Atom a) { out = a.asSymbol()->s_name; }

// -----

template <int I, typename T>
class _tupleFromAtomlistT {
public:
    T& output;

    explicit _tupleFromAtomlistT(T& o)
        : output(o)
    {
    }

    void operator()(const AtomList& src)
    {
        using el_type = decltype(std::get<I - 1>(output));

        auto& el = std::get<I - 1>(output);
        auto atom = src.at(I - 1);

        convertAtom(el, atom);

        AtomList next = src;
        next.remove(next.size() - 1);

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

    explicit AtomListWrapperT(const AtomList& src)
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
