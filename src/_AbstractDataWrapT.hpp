// template class to wrap class into AbstractData

#ifndef AbstractDataWrapT_hpp
#define AbstractDataWrapT_hpp

#include "ceammc_abstractdata.h"
#include "ceammc_data.h"

#include <memory.h>

using namespace ceammc;

template <typename T>
class AbstractDataWrapT : public AbstractData {

public:
    using noRefT = typename std::remove_reference<T>::type;

    std::shared_ptr<noRefT> value = 0;

    virtual AbstractData* clone() const override
    {
        return new AbstractDataWrapT(value);
    }

    virtual DataType type() const override { return typeid(T).hash_code() % 8192; }

    virtual std::string toString() const override
    {
        return typeid(T).name();
    }

    explicit AbstractDataWrapT(noRefT v)
    {
        value = std::make_shared<noRefT>();
        *value = v;
    };

    explicit AbstractDataWrapT(std::shared_ptr<noRefT> v)
    {
        value = v;
    };

    explicit AbstractDataWrapT()
    {
        value = std::make_shared<noRefT>();
    }

    ~AbstractDataWrapT()
    {
        value = 0;
    }

    static const unsigned short dataType;
};

template <typename T>
const unsigned short AbstractDataWrapT<T>::dataType = (typeid(T).hash_code() % 8192);

// ---

#endif
