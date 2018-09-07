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

#include <functional>

//#include "dispatch/dispatch.h"
#include <thread>
// ---

template <typename T, class F>
class ClassStaticMethod : public ceammc::BaseObject {

public:
    using Traits = _functionTraits<F>;

    F _defaultMethod;
    F _method;

    typename Traits::arguments _arguments;

    AtomListFromReturnType<typename Traits::return_type> _return;

    AtomListFromReturnType<F> _funcAtom;

    bool _runInThread = false;
    std::function<void(void)> _theThread;
    std::thread* _thread = 0;
    bool _performThread = false;

    ClassStaticMethod(PdArgs& a, F m)
        : BaseObject(a)
        , _method(m)
    {
        createOutlet();
        createOutlet();

        _funcAtom = AtomListFromReturnType<F>(m);

        _theThread = [&]() {
                    _dispatch();
                    onBang();
        };
        _thread = new std::thread(_theThread);
    };

    ~ClassStaticMethod()
    {
        // the fix. lol
        _method = _defaultMethod;

        if (_thread) {
            _thread->join();
            delete _thread;
        }
    }

    void _dispatch()
    {
        _InvocationStaticMethod<typename Traits::return_type, F, decltype(_arguments)> call = _InvocationStaticMethod<typename Traits::return_type, F, decltype(_arguments)>(_method, _arguments);
        call(typename _genSequence<Traits::arity>::type());

        _return = call._return;
    }

    virtual void onBang() override
    {
        //        auto atom = _return.asAtom();
                auto atomList = _return.asAtomList();
                atomList.output(outletAt(0));
        //        atom.output(outletAt(0));
    }

    virtual void onAny(t_symbol* s, const AtomList& l) override
    {
        if (s == gensym("func")) {
            auto atomList = _funcAtom.asAtomList();
            atomList.output(outletAt(1));
        }

        if (s == gensym("thread")) {
            if (l.size() < 1)
                return;

            _runInThread = l.at(0).asInt() > 0;
        }
    }

    virtual void onList(const AtomList& l) override
    {

        if (l.size() != Traits::arity) {
            post("bad message: expected %i arguments, %i provided", Traits::arity, l.size());
        }

        // set arguments and call function
        ArgumentsFromAtomList<F> converter(l);
        _arguments = converter.output;

        if (_runInThread) {
            post("separate thread *");
            auto t = std::thread(_theThread);
            t.join();

        }

        else {
            _dispatch();
            onBang();
        }
    }

    virtual void
    onFloat(float f) override
    {
        onList(AtomList(Atom(f)));
    }

    virtual void onSymbol(t_symbol* s) override
    {
        onList(AtomList(Atom(s)));
    }
};

#endif
