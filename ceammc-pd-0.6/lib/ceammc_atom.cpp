/*****************************************************************************
 * Copyright 2016 Serge Poltavski. All rights reserved.
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

#include "ceammc_atom.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <sstream>

typedef unsigned int data_id_type;
static const unsigned int MASK_BITS = 12;

// on 32-bit uint - use 2**20 unique object id
// on 64-bit uint - use 2**52 unique object id
static const data_id_type ID_MASK = (std::numeric_limits<data_id_type>::max() >> MASK_BITS);

// use 2**12 unique data types
static const data_id_type TYPE_MASK = ~ID_MASK;
static const unsigned int TYPE_SHIFT = std::numeric_limits<data_id_type>::digits - MASK_BITS;

static const t_atomtype DATA_TYPE = t_atomtype(A_GIMME + 11);

namespace ceammc {

Atom::Atom()
{
    a_type = A_NULL;
}

Atom::Atom(const t_atom& a)
    : t_atom(a)
{
    if (a_type == A_DEFFLOAT)
        a_type = A_FLOAT;
    if (a_type == A_DEFSYMBOL)
        a_type = A_SYMBOL;
}

Atom::Atom(t_float v)
{
    SETFLOAT(this, v);
}

Atom::Atom(t_symbol* s)
{
    SETSYMBOL(this, s);
}

Atom::Atom(const DataDesc& d)
{
    setData(d);
}

bool Atom::isFloat() const
{
    return type() == FLOAT;
}

bool Atom::isNone() const
{
    return type() == NONE;
}

bool Atom::isSymbol() const
{
    return type() == SYMBOL || type() == PROPERTY;
}

bool Atom::isProperty() const
{
    return type() == PROPERTY;
}

bool Atom::isInteger() const
{
    return isFloat() && ceilf(a_w.w_float) == a_w.w_float;
}

bool Atom::isNatural() const
{
    return isInteger() && a_w.w_float >= 0.f;
}

bool Atom::isData() const
{
    return type() == DATA;
}

bool Atom::isDataType(DataType type) const
{
    if (!isData())
        return false;

    return dataType() == type;
}

Atom::Type Atom::type() const
{
    switch (a_type) {
    case A_SYMBOL:
        if (a_w.w_symbol == 0)
            return NONE;

        return (a_w.w_symbol->s_name[0] == PROP_PREFIX) ? PROPERTY : SYMBOL;
    case A_FLOAT:
        return FLOAT;
    case DATA_TYPE:
        return DATA;
    default:
        return NONE;
    }
}

bool Atom::getFloat(t_float* v) const
{
    if (v == 0)
        return false;

    if (!isFloat())
        return false;

    *v = this->a_w.w_float;
    return true;
}

bool Atom::getSymbol(t_symbol** s) const
{
    if (s == 0)
        return false;

    if (!isSymbol())
        return false;

    *s = this->a_w.w_symbol;
    return true;
}

bool Atom::getString(std::string& str) const
{
    if (!isSymbol())
        return false;

    str = this->a_w.w_symbol->s_name;
    return true;
}

bool Atom::setFloat(t_float v, bool force)
{
    if (!force && !isFloat())
        return false;

    SETFLOAT(this, v);
    return true;
}

bool Atom::setSymbol(t_symbol* s, bool force)
{
    if (!force && !isSymbol())
        return false;

    SETSYMBOL(this, s);
    return true;
}

t_float Atom::asFloat(float def) const
{
    return isFloat() ? a_w.w_float : def;
}

int Atom::asInt(int def) const
{
    return isFloat() ? static_cast<int>(a_w.w_float) : def;
}

size_t Atom::asSizeT(size_t def) const
{
    if (!isFloat())
        return def;

    t_float v = a_w.w_float;
    return (v < 0) ? def : static_cast<size_t>(v);
}

t_symbol* Atom::asSymbol() const
{
    return a_w.w_symbol;
}

std::string Atom::asString() const
{
    if (isSymbol())
        return a_w.w_symbol->s_name;
    if (isFloat()) {
        char buf[16];
        if ((a_w.w_float - (int)(a_w.w_float)) < 0.001)
            sprintf(buf, "%.0f", a_w.w_float);
        else
            sprintf(buf, "%.4f", a_w.w_float);
        std::string ret = buf;
        return ret;
    }
    return "";
}

bool Atom::operator<(const Atom& a) const
{
    if (this == &a)
        return false;

    if (this->a_type < a.a_type)
        return true;

    if (isFloat())
        return this->a_w.w_float < a.a_w.w_float;

    if (isSymbol() && a.isSymbol()) {
        if (a_w.w_symbol == a.a_w.w_symbol)
            return false;

        if (a_w.w_symbol == 0 || a.a_w.w_symbol == 0)
            return false;

        if (a_w.w_symbol->s_name == 0 || a.a_w.w_symbol->s_name == 0)
            return false;

        return strcmp(a_w.w_symbol->s_name, a.a_w.w_symbol->s_name) < 0;
    }

    return false;
}

void Atom::output(_outlet* x) const
{
    to_outlet(x, *this);
}

Atom& Atom::operator+=(double v)
{
    if (isFloat())
        a_w.w_float += v;

    return *this;
}

Atom& Atom::operator-=(double v)
{
    if (isFloat())
        a_w.w_float -= v;

    return *this;
}

Atom& Atom::operator*=(double v)
{
    if (isFloat())
        a_w.w_float *= v;

    return *this;
}

Atom& Atom::operator/=(double v)
{
    if (isFloat() && v != 0.0)
        a_w.w_float /= v;

    return *this;
}

Atom Atom::operator+(double v) const
{
    return Atom(*this) += v;
}

Atom Atom::operator-(double v) const
{
    return Atom(*this) -= v;
}

Atom Atom::operator*(double v) const
{
    return Atom(*this) *= v;
}

Atom Atom::operator/(double v) const
{
    return Atom(*this) /= v;
}

void Atom::apply(AtomFloatMapFunction f)
{
    if (isFloat())
        a_w.w_float = f(a_w.w_float);
}

void Atom::apply(AtomSymbolMapFunction f)
{
    if (a_type == A_SYMBOL)
        a_w.w_symbol = f(a_w.w_symbol);
}

DataType Atom::dataType() const
{
    return getData().type;
}

DataId Atom::dataId() const
{
    return getData().id;
}

DataDesc Atom::getData() const
{
    if (a_type != DATA_TYPE)
        return DataDesc(0, 0);

    data_id_type value = static_cast<data_id_type>(a_w.w_index);

    DataType t = (value & TYPE_MASK) >> TYPE_SHIFT;
    DataId id = value & ID_MASK;
    return DataDesc(t, id);
}

void Atom::setData(const DataDesc& d)
{
    a_type = DATA_TYPE;
    data_id_type t = static_cast<unsigned int>(d.type) << TYPE_SHIFT;
    data_id_type id = d.id & ID_MASK;
    data_id_type value = t | id;
    a_w.w_index = value;
}

void Atom::outputAsAny(t_outlet* x, t_symbol* sel) const
{
    outlet_anything(x, sel, 1, const_cast<t_atom*>(static_cast<const t_atom*>(this)));
}

bool operator==(const Atom& a1, const Atom& a2)
{
    if (&a1 == &a2)
        return true;

    if (a1.a_type != a2.a_type)
        return false;

    if (a1.isFloat())
        return a1.a_w.w_float == a2.a_w.w_float;

    if (a1.isSymbol()) {
        if (a1.a_w.w_symbol == a2.a_w.w_symbol)
            return true;

        if (a1.a_w.w_symbol == 0 || a1.a_w.w_symbol == 0)
            return false;

        if (a1.a_w.w_symbol->s_name == 0 || a2.a_w.w_symbol->s_name == 0)
            return false;

        return strcmp(a1.a_w.w_symbol->s_name, a2.a_w.w_symbol->s_name) == 0;
    }

    if (a1.isData() && a2.isData())
        return a1.getData() == a2.getData();

    return false;
}

bool operator!=(const Atom& a1, const Atom& a2)
{
    return !(a1 == a2);
}

bool to_outlet(t_outlet* x, const Atom& a)
{
    if (a.isFloat()) {
        outlet_float(x, a.asFloat());
        return true;
    }

    if (a.isSymbol()) {
        outlet_symbol(x, a.asSymbol());
        return true;
    }

    if (a.isData()) {
        outlet_list(x, &s_list, 1, const_cast<t_atom*>(reinterpret_cast<const t_atom*>(&a)));
        return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, const Atom& a)
{
    if (a.isFloat())
        os << a.asFloat();
    if (a.isSymbol())
        os << a.asString();
    if (a.isNone())
        os << "NONE";
    if (a.isData())
        os << "Data[" << a.dataType() << '#' << a.dataId() << ']';

    return os;
}

DataDesc::DataDesc(DataType t, DataId i)
    : type(t)
    , id(i)
{
}

bool DataDesc::operator==(const DataDesc& d) const
{
    return type == d.type && id == d.id;
}

bool DataDesc::operator!=(const DataDesc& d) const
{
    return !(this->operator==(d));
}
}
