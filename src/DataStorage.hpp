// creates Pd object for static method

#ifndef DataStorage_hpp
#define DataStorage_hpp

#include "global_base.h"
#include "local_base.h"

#include "_AbstractDataWrapT.hpp"

template <typename T>
class WrapLocalData : public ceammc::LocalBase<AbstractDataWrapT<T> > {
public:
    WrapLocalData(const PdArgs& a)
        : LocalBase<AbstractDataWrapT<T> >(a){

        };

    virtual void onBang() override
    {
        BaseObject::dataTo(0, ceammc::LocalBase<AbstractDataWrapT<T> >::ref().clone());
    }

    virtual void onList(const AtomList& l) override
    {

        if (l.at(0).isData()) {

            DataAtom da(l.at(0));

            if (!da.isData()) {
                post("bad ptr");
                return;
            }

            if (da.isAtom()) {
                post("bad ptr - atom");
                return;
            }

            if (da.data().isNull()) {
                post("null pointer");
                return;
            }

            auto v = const_cast<AbstractDataWrapT<T>*>(da.as<AbstractDataWrapT<T> >());
            ceammc::GlobalBase<AbstractDataWrapT<T> >::ref() = *v; //DataTPtr<AbstractDataWrapT<T> >(l.at(0));

            return;
        }
    }
};

template <typename T>
class WrapGlobalData : public ceammc::GlobalBase<AbstractDataWrapT<T> > {

public:
    WrapGlobalData(const PdArgs& a)
        : GlobalBase<AbstractDataWrapT<T> >(a){

        };

    virtual void onBang() override
    {
        BaseObject::dataTo(0, ceammc::GlobalBase<AbstractDataWrapT<T> >::ref().clone());
    }

    virtual void onList(const AtomList& l) override
    {

        if (l.at(0).isData()) {

            DataAtom da(l.at(0));

            if (!da.isData()) {
                post("bad ptr");
                return;
            }

            if (da.isAtom()) {
                post("bad ptr - atom");
                return;
            }

            if (da.data().isNull()) {
                post("null pointer");
                return;
            }

            auto v = const_cast<AbstractDataWrapT<T>*>(da.as<AbstractDataWrapT<T> >());
            ceammc::GlobalBase<AbstractDataWrapT<T> >::ref() = *v; //DataTPtr<AbstractDataWrapT<T> >(l.at(0));

            return;
        }
    }
};

#endif
