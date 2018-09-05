// creates Pd object for static method

#ifndef ClassStaticMethod_hpp
#define ClassStaticMethod_hpp

#include "ceammc_object.h"

#include "_AtomListWrapperT.hpp"
#include "_FunctionTraits.hpp"
#include "_Invocations.hpp"

#include "ceammc_atomlist.h"
#include "ceammc_dataatom.h"
#include "ceammc_log.h"

// ---

template <typename T, class F>
class ClassStaticMethod : public ceammc::BaseObject {

public:
    using Traits = _functionTraits<F>;

    F _defaultMethod;
    F _method;

    typename Traits::arguments _arguments;

    TypedAtomT<typename Traits::return_type> _return;

    ClassStaticMethod(PdArgs& a, F m)
        : BaseObject(a)
        , _method(m)
    {
        createOutlet();
    };

    ~ClassStaticMethod()
    {
        // the fix. lol
        _method = _defaultMethod;
    }

    void _dispatch()
    {
        _InvocationStaticMethod<typename Traits::return_type, F, decltype(_arguments)> call = _InvocationStaticMethod<typename Traits::return_type, F, decltype(_arguments)>(_method, _arguments);
        call(typename _genSequence<Traits::arity>::type());

        _return = call._return;
    }

    virtual void onBang() override
    {
        _dispatch();
        auto atom = _return.asAtom();
        atom.output(outletAt(0));
    }

    virtual void onAny(t_symbol* s, const AtomList& l) override
    {
    }

    virtual void onList(const AtomList& l) override
    {

        if (l.size() != Traits::arity) {
            post("bad message: expected %i arguments, %i provided", Traits::arity, l.size());
        }

        // set arguments and call function
        AtomListWrapperT<F> converter(l);
        _arguments = converter.output;

        onBang();
    }

    virtual void onFloat(float f) override
    {
        onList(AtomList(Atom(f)));
    }

    virtual void onSymbol(t_symbol* s) override
    {
        onList(AtomList(Atom(s)));
    }
};

#endif
