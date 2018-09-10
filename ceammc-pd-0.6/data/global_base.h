/*****************************************************************************
 * Copyright 2017 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#ifndef GLOBAL_BASE_H
#define GLOBAL_BASE_H

#include "ceammc_format.h"
#include "ceammc_globaldata.h"
#include "ceammc_object.h"

namespace ceammc {

template <typename T>
class GlobalBase : public BaseObject {
    GlobalData<T> data_;
    GlobalBase(const GlobalBase&);
    void operator=(const GlobalBase&);

public:
    GlobalBase(const PdArgs& a)
        : BaseObject(a)
        , data_(a.args.empty() ? "default" : to_string(a.args[0]), a.className->s_name)
    {
        if (positionalArguments().empty())
            OBJ_DBG << "global object ID required! Using default id: \"" << data_.name() << '"';

        createOutlet();
        createCbProperty("@id", &GlobalBase::m_id);
        createCbProperty("@obj_refs", &GlobalBase::m_refs);
        createCbProperty("@obj_keys", &GlobalBase::m_keys);
    }

    T& ref() { return data_.ref(); }
    const T& ref() const { return data_.ref(); }

    size_t refCount() const { return data_.refCount(); }

    AtomList m_id() const
    {
        return listFrom(data_.name());
    }

    AtomList m_keys() const
    {
        std::vector<std::string> keys;
        data_.keys(keys);
        return listFrom(keys);
    }

    AtomList m_refs() const
    {
        return listFrom(data_.refCount());
    }
};
}

#endif // GLOBAL_BASE_H
