// ----------

#include "ClassConstructor.hpp"
#include "ClassMethod.hpp"

#include "DataStorage.hpp"

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
    class L_##y : public WrapLocalData<x> {  \
    public:                               \
        L_##y(PdArgs& a)                 \
            : WrapLocalData<x>(a)             \
        {                                 \
        }                                 \
    };                                    \
                                          \
    class G_##y : public WrapGlobalData<x> { \
    public:                               \
        G_##y(PdArgs& a)                 \
            : WrapGlobalData<x>(a)             \
        {                                 \
        }                                 \
    };                                    \
    ObjectFactory<L_##y>((std::string("local.")+std::string(z)).c_str());             \
    ObjectFactory<G_##y>((std::string("global.")+std::string(z)).c_str());
