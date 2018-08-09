// creates Pd object for class

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
//        post("data ptr out %p", _data.data());
//        post("data ptr toString %s", _data.data()->toString().c_str());
//        post("data id desc %i %i",_data.desc().id,_data.desc().type);


        dataTo(0, _data);
    }
};

#endif
