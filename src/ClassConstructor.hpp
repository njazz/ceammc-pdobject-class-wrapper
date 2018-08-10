// creates Pd object for class
// currently doesn't support constructors with arguments

#ifndef ClassConstructor_hpp
#define ClassConstructor_hpp

#include "ceammc_atomlist.h"
#include "ceammc_factory.h"
#include "ceammc_object.h"

#include "_AbstractDataWrapT.hpp"

using namespace ceammc;

template <typename T>
class ClassConstructor : public ceammc::BaseObject {
    AbstractDataWrapT<T> _value;// = 0;
    DataTPtr<AbstractDataWrapT<T> > _data;

public:
    ClassConstructor(PdArgs& a)
        : BaseObject(a),
         _data(&_value)
        {
            createOutlet();
        };

    ~ClassConstructor()
    {
        _data = 0;
    }

    virtual void onBang() override
    {
        dataTo(0, _data);
    }
};

// ---

#include "_FunctionTraits.hpp"
#include "_Invocations.hpp"

template <typename T, typename F>
class ClassConstructorCustom : public ceammc::BaseObject {
    using Traits = _functionTraits<F>;

//    const F _method;
    typename Traits::arguments _arguments;

    AbstractDataWrapT<T>* _value = 0;
    DataTPtr<AbstractDataWrapT<T> > _data;

public:
    ClassConstructorCustom(PdArgs& a)
        : BaseObject(a),
         _data(0)//,
//       _method(m)
        {
            createOutlet();
        };

    ~ClassConstructorCustom()
    {
        _data = 0;
    }

    virtual void onBang() override
    {
        dataTo(0, _data);
    }

    virtual void onFloat(float f) override
    {
        onList(AtomList(Atom(f)));
    }

    virtual void onSymbol(t_symbol* s) override
    {
        onList(AtomList(Atom(s)));
    }

    void _dispatch()
    {
//        if (!_data.data()) {
//            post("no data");
//            return;
//        }

        _InvocationCustomConstructor< T, F, decltype(_arguments)> call = _InvocationCustomConstructor< T, F, decltype(_arguments)>( _arguments);
        auto ptr = call(typename _genSequence<Traits::arity>::type());

        post ("created class pointer %p", ptr);

        _value = new AbstractDataWrapT<T>(ptr);
        _data = DataTPtr<AbstractDataWrapT<T> >(_value);
    }

    virtual void onList(const AtomList& l) override
    {
        //
        if (l.size() != Traits::arity) {
            post("bad message: expected %i arguments, %i provided", Traits::arity, l.size());
        }

        // set arguments and call function
        AtomListWrapperT<F> converter(l);
        _arguments = converter.output;

        // onBang in ClassMethod:
        _dispatch();
        dataTo(0, _data);

    }

};

#endif
