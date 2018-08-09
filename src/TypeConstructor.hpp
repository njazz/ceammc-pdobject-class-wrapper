// creates Pd object for class
// currently doesn't support constructor's arguments

#ifndef TypeConstructor_hpp
#define TypeConstructor_hpp

#include "ceammc_atomlist.h"
#include "ceammc_factory.h"
#include "ceammc_object.h"

#include "_AbstractDataWrapT.hpp"

using namespace ceammc;

template <typename T>
class TypeConstructor : public ceammc::BaseObject {
    AbstractDataWrapT<T> _value;// = 0;
    DataTPtr<AbstractDataWrapT<T> > _data;

public:
    TypeConstructor(PdArgs& a)
        : BaseObject(a),
         _data(&_value)
        {
            createOutlet();
        };

    ~TypeConstructor()
    {
        _data = 0;
    }

    virtual void onBang() override
    {
        dataTo(0, _data);
    }
};

#endif
