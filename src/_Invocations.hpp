#ifndef _Invocations_hpp
#define _Invocations_hpp

#include "_AtomListWrapperT.hpp"
#include "_FunctionTraits.hpp"

template <typename R, class C, class F, typename A>
class _InvocationClassMethod {
public:
    C& _class;
    const F& _method;
    const A& _arguments;

    TypedAtomT<R> _return;

    _InvocationClassMethod(const C& c, const F& f, const A& a)
        : _class(const_cast<C&>(c))
        , _method(f)
        , _arguments(a)
    {
    }

    template <int... S>
    void operator()(_sequence<S...>)
    {
        _return = TypedAtomT<R>((_class.*_method)(std::get<S>(_arguments)...));
    }
};

// void return type
template <class C, class F, typename A>
class _InvocationClassMethod<void, C, F, A> {
public:
    C& _class;
    const F& _method;
    const A& _arguments;

    TypedAtomT<void> _return;

    _InvocationClassMethod(const C& c, const F& f, const A& a)
        : _class(const_cast<C&>(c))
        , _method(f)
        , _arguments(a)
    {
    }

    template <int... S>
    void operator()(_sequence<S...>)
    {
        (_class.*_method)(std::get<S>(_arguments)...);
    }
};

// ---


template <typename R, class F, typename A>
class _InvocationStaticMethod {
public:
    const F& _method;
    const A& _arguments;

    TypedAtomT<R> _return;

    _InvocationStaticMethod(const F& f, const A& a)
        :
         _method(f)
        , _arguments(a)
    {
    }

    template <int... S>
    void operator()(_sequence<S...>)
    {
        _return = TypedAtomT<R>((*_method)(std::get<S>(_arguments)...));
    }
};

// void return type
template < class F, typename A>
class _InvocationStaticMethod<void,F, A> {
public:
    const F& _method;
    const A& _arguments;

    TypedAtomT<void> _return;

    _InvocationStaticMethod( const F& f, const A& a)
        :  _method(f)
        , _arguments(a)
    {
    }

    template <int... S>
    void operator()(_sequence<S...>)
    {
        (*_method)(std::get<S>(_arguments)...);
    }
};

#endif
