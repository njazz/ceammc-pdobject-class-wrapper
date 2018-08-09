// ----------

#define WRAP_CLASS(x, y)                                \
    class _C_##x : public TypeConstructor<x> { \
    public:                                             \
        _C_##x(PdArgs& a)                      \
            : TypeConstructor<x>(a)                     \
        {                                               \
        }                                               \
    };                                                  \
    ObjectFactory<_C_##x>(y);

#define WRAP_METHOD(x, y, z)                                     \
    constexpr decltype(&x::y) _##x_method_##y = &x::y;           \
    class _##x_##y : public TypeMethod<x, decltype(&x::y)> {     \
                                                                 \
    public:                                                      \
        _##x_##y(PdArgs& a)                                      \
            : TypeMethod<x, decltype(&x::y)>(a, _##x_method_##y) \
        {                                                        \
        }                                                        \
    };                                                           \
    ObjectFactory<_##x_##y>(z)
