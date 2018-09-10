// ----------

#include "ClassConstructor.hpp"
#include "ClassMethod.hpp"

#include "global_base.h"
#include "local_base.h"

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
    ObjectFactory<M_##m>(z);

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
    ObjectFactory<M_##m>(z);

#define WRAP_FUNCTION(y, z, m, n)                     \
                                                      \
    class M_##m : public ClassStaticMethod<void, n> { \
                                                      \
    public:                                           \
        M_##m(PdArgs& a)                              \
            : ClassStaticMethod<void, n>(a, m)        \
        {                                             \
        }                                             \
    };                                                \
    ObjectFactory<M_##m>(z);

#define WRAP_STORAGE(x,y, z)                \
    class L_##y : public LocalBase<x> {  \
    public:                               \
        L_##y(PdArgs& a)                 \
            : LocalBase<x>(a)             \
        {                                 \
        }                                 \
    };                                    \
                                          \
    class G_##y : public GlobalBase<x> { \
    public:                               \
        G_##y(PdArgs& a)                 \
            : GlobalBase<x>(a)             \
        {                                 \
        }                                 \
    };                                    \
    ObjectFactory<L_##y>((std::string("local.")+std::string(z)).c_str());             \
    ObjectFactory<G_##y>((std::string("global.")+std::string(z)).c_str());
