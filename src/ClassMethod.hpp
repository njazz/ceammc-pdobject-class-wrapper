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

    F _defaultMethod;
    F _method;

    AtomListFromReturnType<F> _funcAtom;

    typename Traits::arguments _arguments;

    AtomListFromReturnType<typename Traits::return_type> _return;

    ClassMethod(PdArgs& a, F m) //F m)
        : BaseObject(a) //
          ,_method(m)
    {
        createOutlet();
        createOutlet();

        // TODO: output lambda
        _funcAtom = AtomListFromReturnType<F>(m);

    };

    ~ClassMethod()
    {
        _method = _defaultMethod;
        _data = 0;
    }

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

            post("class method received data: id: %i desc: %i pointer: %p ", l.at(0).getData().id, l.at(0).getData().type,da.data().data());

            if (!da.isData()) {
                post("bad ptr");
                return;
            }

            if (da.isAtom()) {
                post("bad ptr - atom");
                return;
            }

            if (da.data().isNull())
                post("null pointer");

            _data = DataTPtr<AbstractDataWrapT<T> >(l.at(0));

            return;
        }

        //
        if (l.size() != Traits::arity) {
            post("bad message: expected %i arguments, %i provided", Traits::arity, l.size());
        }

        // set arguments and call function
        ArgumentsFromAtomList<F> converter(l);
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
