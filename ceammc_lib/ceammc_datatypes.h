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
#ifndef CEAMMC_DATATYPES_H
#define CEAMMC_DATATYPES_H

#include "ceammc_atom.h"

namespace ceammc {
namespace data {
    static const ::ceammc::DataType DATA_INVALID = ::ceammc::DataType(-1);
    static const ::ceammc::DataType DATA_STRING = 1;
    static const ::ceammc::DataType DATA_SET = 2;
    static const ::ceammc::DataType DATA_DICT = 3;
}
}

#endif // CEAMMC_DATATYPES_H
