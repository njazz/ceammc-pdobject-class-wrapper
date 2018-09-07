// converts AtomList <-> tuple

#ifndef AtomListWrapperT_hpp
#define AtomListWrapperT_hpp

#include "_AbstractDataWrapT.hpp"
#include "_FunctionTraits.hpp"
#include "_SequenceT.hpp"

#include "ceammc_atomlist.h"
#include "ceammc_data.h"
#include "ceammc_dataatom.h"

#include "_Converters.hpp"

// ---------------------

template <int I, typename T>
class _tupleFromAtomlistT {

    // converts n elements to T; erases them, returns false if l.size is zero.
    template <typename U>
    bool _process(U& v, AtomList& l)
    {
        if (l.size() < 1)
            return false;

        int n = _fromAtomList(v, l);

        for (int i = 0; i < n; i++) {
            l.remove(l.size() - 1);
        }
        return true;
    }

public:
    T& output;

    explicit _tupleFromAtomlistT(T& o)
        : output(o)
    {
    }

    void operator()(const AtomList& src)
    {
        using elementType = decltype(std::get<I - 1>(output));

        auto& element = std::get<I - 1>(output);

        AtomList nextList = src;
        bool result = _process(element, nextList);

        if (result)
            tail(nextList);
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
class ArgumentsFromAtomList : public AtomList {
    using Traits = _functionTraits<F>;

public:
    typename Traits::arguments output;
    bool validOutput = false;

    explicit ArgumentsFromAtomList(const AtomList& src)
    {
        constexpr size_t tupleSize = std::tuple_size<typename Traits::arguments>::value;

        validOutput = true;

        if (src.size() != tupleSize) {
            validOutput = false;
            //            return;
        }

        _tupleFromAtomlistT<tupleSize, typename Traits::arguments> proc(output);
        proc(src);
    };
};

#endif
