// creates Pd object for class method

#ifndef ClassMethod_hpp
#define ClassMethod_hpp

#include "ceammc_object.h"

#include "_AtomListWrapperT.hpp"
#include "_FunctionTraits.hpp"
#include "_Invocations.hpp"

#include "ceammc_atomlist.h"
#include "ceammc_dataatom.h"
#include "ceammc_log.h"

// ---

template <typename T, class F>
class ClassMethod : public ceammc::BaseObject {
    DataTPtr<AbstractDataWrapT<T> > _data = DataTPtr<AbstractDataWrapT<T> >(Atom());

public:
    using Traits = _functionTraits<F>;

    const F _method;
    typename Traits::arguments _arguments;

    TypedAtomT<typename Traits::return_type> _return;

    ClassMethod(PdArgs& a, F m) //F m)
        : BaseObject(a) //
          ,_method(m)
    {
        createOutlet();
    };

    void _dispatch()
    {
        if (!_data.data()) {
            post("no data");
            return;
        }

        _InvocationClassMethod<typename Traits::return_type, T, F, decltype(_arguments)> call = _InvocationClassMethod<typename Traits::return_type, T, F, decltype(_arguments)>(*_data.data()->value, _method, _arguments);
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
        if (s == gensym("set"))
            if (l.size() == 1)
                if (l.at(0).isData()) {
                    _data = DataTPtr<AbstractDataWrapT<T> >(l.at(0)); //d.data();
                }
    }

    virtual void onData(const DataPtr& d) override
    {
        post("data %i vs %i", d.desc().type, _data.desc().type);

        if (d.desc().type == _data.desc().type) {
            _data = DataTPtr<AbstractDataWrapT<T> >(d.asAtom());
        }
    }

    virtual void onList(const AtomList& l) override
    {

        if (l.at(0).isData()) {

            DataAtom da(l.at(0));

            post("rcv data id desc %i %i", l.at(0).getData().id, l.at(0).getData().type);
            post("rcv data: %p", da.data().data());

            if (!da.isData()) {
                post("bad ptr");
                return;
            }

            if (da.isAtom()) {
                post("bad ptr - atom");
                return;
            }

            post("null %i", da.data().isNull());

            _data = DataTPtr<AbstractDataWrapT<T> >(l.at(0));

            return;
        }

        //
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
