// ----------

#include "ClassMethod.hpp"
#include "ClassConstructor.hpp"

#define WRAP_CLASS(x, y)                       \
    class _C_##x : public ClassConstructor<x> { \
    public:                                    \
        _C_##x(PdArgs& a)                      \
            : ClassConstructor<x>(a)            \
        {                                      \
        }                                      \
    };                                         \
    ObjectFactory<_C_##x>(y);

// ---

#define WRAP_METHOD(x, y, z, m, n)                               \
    /* constexpr decltype(&x::y) _##x_method_##y = &x::y;     */ \
                                                                 \
    class M_##m : public ClassMethod<x, n> {                      \
                                                                \
                                                                 \
            public : M_##m(PdArgs& a)                            \
            : ClassMethod<x, n>(a, m)                             \
        {                                                        \
        }                                                        \
    };                                                           \
    ObjectFactory<M_##m>(z)
