// template class to wrap class into AbstractData

#ifndef AbstractDataWrapT_hpp
#define AbstractDataWrapT_hpp

#include "ceammc_abstractdata.h"
#include "ceammc_data.h"

#include <memory.h>

#include <cxxabi.h>

#include <algorithm>
#include <string>

using namespace ceammc;

template <typename T>
class AbstractDataWrapT : public AbstractData {

public:
    using noRefT = typename std::remove_reference<T>::type;

    std::shared_ptr<noRefT> value = 0;

    explicit AbstractDataWrapT(noRefT v)
    {
        value = std::make_shared<noRefT>();
        *value = v;
    };

    explicit AbstractDataWrapT(std::shared_ptr<noRefT> v)
    {
        value = v;
        *value = *v;
    };

    explicit AbstractDataWrapT()
    {
        value = std::make_shared<noRefT>();
    }

    ~AbstractDataWrapT()
    {
        value = 0;
    }

    AbstractDataWrapT& operator=(AbstractDataWrapT& in)
    {
        value = in.value;
        *value = *in.value;

        return(*this);
    }

    virtual AbstractData* clone() const override
    {
        return new AbstractDataWrapT(value);
    }

    virtual DataType type() const override { return AbstractDataWrapT<T>::dataType;}//typeid(T).hash_code() % 8192; }

    inline static void _replace(std::string& str, std::string src, std::string dest)
    {
        size_t pos = str.find(src);
        while (pos != std::string::npos) {
            str.replace(pos, src.size(), dest);
            pos = str.find(src, pos + src.size());
        }
    }
    virtual std::string toString() const override
    {
        int status;
        std::string abi_str = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
        return abi_str;
    }

    static const unsigned short dataType;
};

template <typename T>
const unsigned short AbstractDataWrapT<T>::dataType = (typeid(T).hash_code() % 8192);

// ---

#endif
