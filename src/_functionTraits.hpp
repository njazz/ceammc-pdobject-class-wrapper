// function traits

#ifndef Traits_hpp
#define Traits_hpp

template<class F>
struct _functionTraits;

// function pointer
template<class R, class... Args>
struct _functionTraits<R(*)(Args...)> : public _functionTraits<R(Args...)>
{};

template<class R, class... Args>
struct _functionTraits<R(Args...)>
{
    using return_type = R;

    static constexpr std::size_t arity = sizeof...(Args);

    template <std::size_t N>
    struct argument
    {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename std::tuple_element<N,std::tuple<Args...>>::type;
    };
    using arguments = typename std::tuple<Args...>;
};

template<class R, class C, class... Args>
struct _functionTraits<R(C&,Args...)>
{
    using return_type = R;
    using object_type = C;

    static constexpr std::size_t arity = sizeof...(Args);

    template <std::size_t N>
    struct argument
    {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename std::tuple_element<N,std::tuple<Args...>>::type;
    };

    using arguments = typename std::tuple<Args...>;
};

// member function pointer
template<class C, class R, class... Args>
struct _functionTraits<R(C::*)(Args...)> : public _functionTraits<R(C&,Args...)>
{};

// const member function pointer
template<class C, class R, class... Args>
struct _functionTraits<R(C::*)(Args...) const> : public _functionTraits<R(C&,Args...)>
{};

// member object pointer
template<class C, class R>
struct _functionTraits<R(C::*)> : public _functionTraits<R(C&)>
{};

#endif
