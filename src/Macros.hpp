// ----------

#include "ClassConstructor.hpp"
#include "ClassMethod.hpp"

#define WRAP_CLASS(x, y)                        \
  /*  class _C_##x : public ClassConstructor<x> { \
    public:                                     \
        _C_##x(PdArgs& a)                       \
            : ClassConstructor<x>(a)            \
        {                                       \
        }                                       \
    };                                          \*/ \
    ObjectFactory<ClassConstructor<x> >(y);

// ---

#define WRAP_METHOD(x, y, z, m, n)                               \
    /* constexpr decltype(&x::y) _##x_method_##y = &x::y;     */ \
                                                                 \
    class M_##m : public ClassMethod<x, n> {                     \
                                                                 \
    public:                                                      \
        M_##m(PdArgs& a)                                         \
            : ClassMethod<x, n>(a, m)                            \
        {                                                        \
        }                                                        \
    };                                                           \
    ObjectFactory<M_##m>(z)

// ---

#define WRAP_STATIC_METHOD(x, y, z, m, n)                        \
    /* constexpr decltype(&x::y) _##x_method_##y = &x::y;     */ \
                                                                 \
    class M_##m : public ClassStaticMethod<x, n> {               \
                                                                 \
    public:                                                      \
        M_##m(PdArgs& a)                                         \
            : ClassStaticMethod<x, n>(a, m)                      \
        {                                                        \
        }                                                        \
    };                                                           \
    ObjectFactory<M_##m>(z)
