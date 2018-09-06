// ----------

#include "ClassConstructor.hpp"
#include "ClassMethod.hpp"

#define WRAP_CLASS(x, y) ObjectFactory<ClassConstructor<x> >(y);
#define WRAP_CUSTOM_CLASS(x, y, z, m, n)                \
    class C_##m : public ClassConstructorCustom<x, n> { \
    public:                                             \
        C_##m(PdArgs& a)                                \
            : ClassConstructorCustom<x, n>(a)           \
        {                                               \
        }                                               \
    };                                                  \
    ObjectFactory<C_##m>(z);

// ---

#define WRAP_METHOD(x, y, z, m, n)           \
                                             \
    class M_##m : public ClassMethod<x, n> { \
                                             \
    public:                                  \
        M_##m(PdArgs& a)                     \
            : ClassMethod<x, n>(a, m)        \
        {                                    \
        }                                    \
    };                                       \
    ObjectFactory<M_##m>(z)

// ---

#define WRAP_STATIC_METHOD(x, y, z, m, n)          \
                                                   \
    class M_##m : public ClassStaticMethod<x, n> { \
                                                   \
    public:                                        \
        M_##m(PdArgs& a)                           \
            : ClassStaticMethod<x, n>(a, m)        \
        {                                          \
        }                                          \
    };                                             \
    ObjectFactory<M_##m>(z)

#define WRAP_FUNCTION(y, z, m, n)          \
                                                   \
    class M_##m : public ClassStaticMethod<void, n> { \
                                                   \
    public:                                        \
        M_##m(PdArgs& a)                           \
            : ClassStaticMethod<void, n>(a, m)        \
        {                                          \
        }                                          \
    };                                             \
    ObjectFactory<M_##m>(z)

#include "StructField.hpp"
#define WRAP_FIELD(x, m, n)\
    // TODO

