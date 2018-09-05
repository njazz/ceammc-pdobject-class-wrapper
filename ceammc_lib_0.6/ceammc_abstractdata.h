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
#ifndef CEAMMC_ABSTRACTDATA_H
#define CEAMMC_ABSTRACTDATA_H

#include "ceammc_atom.h"

namespace ceammc {

/**
 * @brief Base class for all data types
 */
class AbstractData {
public:
    virtual ~AbstractData();

    /**
     * override this method to dump data to Pd console
     */
    virtual void dump() {}

    /**
     * This method should return pointer to new dynamically allocated copy of data
     */
    virtual AbstractData* clone() const = 0;

    /**
     * This method should return ID to data type.
     */
    virtual DataType type() const = 0;

    /**
     * Override this method to get non-default string data representation
     */
    virtual std::string toString() const;

    /**
     * Override this method to compare data by pointer to base class
     */
    virtual bool isEqual(const AbstractData* d) const;

    /**
     * Override this method to compare data by pointer to base class
     */
    virtual bool isLess(const AbstractData* d) const;

    /**
     * Helper functions to return pointer to derived classes
     */
    template <class T>
    T* as();
    template <class T>
    const T* as() const;

    /**
     * Typed version of clone() method
     */
    template <class T>
    T* cloneT() const;
};

template <class T>
T* AbstractData::cloneT() const
{
    if (type() != T::dataType)
        return 0;

    return static_cast<T*>(clone());
}

template <class T>
T* AbstractData::as()
{
    return type() == T::dataType ? static_cast<T*>(this) : 0;
}

template <class T>
const T* AbstractData::as() const
{
    return type() == T::dataType ? static_cast<const T*>(this) : 0;
}
}

#endif // CEAMMC_ABSTRACTDATA_H
