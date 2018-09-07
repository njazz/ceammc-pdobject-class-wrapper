/*****************************************************************************
 * Copyright 2018 Serge Poltavsky. All rights reserved.
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
#include "ceammc_sound_external.h"

#include <algorithm>

namespace ceammc {
SoundExternal::SoundExternal(const PdArgs& a)
    : BaseObject(a)
    , block_size_(0)
    , n_in_(a.hasDefaultSignalInlet() ? 1 : 0)
    , n_out_(0)
    , sample_rate_(44100)
{
}

void SoundExternal::setupDSP(t_signal** sp)
{
    block_size_ = size_t(sp[0]->s_n);
    sample_rate_ = size_t(sp[0]->s_sr);

    dsp_add(dspPerform, 1, static_cast<void*>(this));

    for (size_t i = 0; i < n_in_; i++)
        in_[i] = sp[i]->s_vec;

    for (size_t i = 0; i < n_out_; i++)
        out_[i] = sp[i + n_in_]->s_vec;
}

t_inlet* SoundExternal::createSignalInlet()
{
    if (n_in_ == MAX_SIG_NUM) {
        OBJ_ERR << "too many inlets: " << n_in_;
        return 0;
    }

    t_inlet* in = inlet_new(owner(), &owner()->ob_pd, &s_signal, &s_signal);
    appendInlet(in);
    n_in_++;
    return in;
}

t_outlet* SoundExternal::createSignalOutlet()
{
    if (n_out_ == MAX_SIG_NUM) {
        OBJ_ERR << "too many outlets: " << n_out_;
        return 0;
    }

    t_outlet* out = outlet_new(owner(), &s_signal);
    appendOutlet(out);
    n_out_++;
    return out;
}

void SoundExternal::dump() const
{
    BaseObject::dump();
    post("[%s] block size: %i", className().c_str(), blockSize());
    post("[%s] samplerate: %i", className().c_str(), samplerate());
}
}
