/*****************************************************************************
 * Copyright 2016 Serge Poltavsky. All rights reserved.
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
#include "ceammc_impl.h"

#include <m_pd.h>

#include "m_imp.h"

namespace ceammc {

PdFloatFunction default_pd_float_fn(t_class* c)
{
    return reinterpret_cast<PdFloatFunction>(c->c_floatmethod);
}

PdBangFunction default_pd_bang_fn(t_class* c)
{
    return reinterpret_cast<PdBangFunction>(c->c_bangmethod);
}

} // namespace ceammc
