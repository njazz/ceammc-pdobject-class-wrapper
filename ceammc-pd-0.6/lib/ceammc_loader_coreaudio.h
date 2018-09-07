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
#ifndef CEAMMC_LOADER_COREAUDIO_H
#define CEAMMC_LOADER_COREAUDIO_H

#include "ceammc_sound.h"

namespace ceammc {
namespace sound {
    class CoreAudioFile : public SoundFile {
        std::string fname_;
        size_t sample_rate_;
        size_t channels_;
        size_t sample_count_;
        bool is_opened_;

    public:
        CoreAudioFile(const std::string& fname);
        size_t sampleCount() const;
        size_t sampleRate() const;
        size_t channels() const;
        bool isOpened() const;
        bool close();

        long read(t_word* dest, size_t sz, size_t channel, long offset = 0);

    public:
        static FormatList supportedFormats();
    };
}
}

#endif // CEAMMC_LOADER_COREAUDIO_H
