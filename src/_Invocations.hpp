#ifndef _Invocations_hpp
#define _Invocations_hpp

#include "_AtomListWrapperT.hpp"
#include "_FunctionTraits.hpp"

#include <memory.h>

template <typename R, class C, class F, typename A>
class _InvocationClassMethod {
public:
    C& _class;
    const F& _method;
    const A& _arguments;

    AtomListFromReturnType<R> _return;

    _InvocationClassMethod(const C& c, const F& f, const A& a)
        : _class(const_cast<C&>(c))
        , _method(f)
        , _arguments(a)
    {
    }

    template <int... S>
    void operator()(_sequence<S...>)
    {
        _return = AtomListFromReturnType<R>((_class.*_method)(std::get<S>(_arguments)...));
    }
};

// void return type
template <class C, class F, typename A>
class _InvocationClassMethod<void, C, F, A> {
public:
    C& _class;
    const F& _method;
    const A& _arguments;

    AtomListFromReturnType<void> _return;

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

    AtomListFromReturnType<R> _return;

    _InvocationStaticMethod(const F& f, const A& a)
        : _method(f)
        , _arguments(a)
    {
    }

    template <int... S>
    void operator()(_sequence<S...>)
    {
        _return = AtomListFromReturnType<R>((*_method)(std::get<S>(_arguments)...));
    }
};

// void return type
template <class F, typename A>
class _InvocationStaticMethod<void, F, A> {
public:
    const F& _method;
    const A& _arguments;

    AtomListFromReturnType<void> _return;

    _InvocationStaticMethod(const F& f, const A& a)
        : _method(f)
        , _arguments(a)
    {
    }

    template <int... S>
    void operator()(_sequence<S...>)
    {
        (*_method)(std::get<S>(_arguments)...);
    }
};

// custom constructor
template <typename R, class F, typename A>
class _InvocationCustomConstructor {
public:
    const A& _arguments;

    explicit _InvocationCustomConstructor(const A& a)
        : _arguments(a)
    {
    }

    template <int... S>
    std::shared_ptr<R> operator()(_sequence<S...>)
    {
        return std::make_shared<R>(std::get<S>(_arguments)...);
    }
};

#endif
