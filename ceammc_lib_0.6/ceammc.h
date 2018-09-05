/*****************************************************************************
 *
 * Created: 17.10.2016 2016 by Serge Poltavski
 *
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
#ifndef CEAMMC_H
#define CEAMMC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "m_pd.h"

#include <stddef.h>

/**
 * @brief compare atoms
 * @return 0 - if a1 == a2, _-1); -1 - if a1 < a2; +1 - if a1 > a2
 * @see ceammc_atoms_equal
 */
int ceammc_atoms_compare(const t_atom* a1, const t_atom* a2);

t_atom* ceammc_atoms_alloc(size_t n);
void ceammc_atoms_free(t_atom* mem, size_t n);
t_atom* ceammc_atoms_alloc_copy(size_t, t_atom* from);
void output_atom(t_outlet* out, t_atom* atom);

typedef t_float (*ceammc_float_unary_func)(t_float);
typedef t_float (*ceammc_float_binary_func)(t_float, t_float);
void ceammc_atoms_map_float(size_t n, t_atom* a, ceammc_float_unary_func func);
void ceammc_atoms_map_float_to_outlet(t_outlet* o, t_symbol* s, int n, t_atom* a, ceammc_float_unary_func func);

size_t ceammc_memory_size();
size_t ceammc_memory_current_rss();
size_t ceammc_memory_peak_rss();

#ifdef __cplusplus
}
#endif

#endif // CEAMMC_H
