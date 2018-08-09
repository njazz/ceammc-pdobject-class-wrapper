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
#ifndef CEAMMC_LOADER_COREAUDIO_IMPL_H
#define CEAMMC_LOADER_COREAUDIO_IMPL_H

#include <m_pd.h>
#include <stdint.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct audio_fileinfo_ {
    size_t sampleRate;
    size_t channels;
    size_t sampleCount;
} audiofile_info_t;

enum ceammc_coreaudio_error {
    INVALID_ARGS = -1,
    FILEOPEN_ERR = -2,
    FILEINFO_ERR = -3,
    PROPERTY_ERR = -4,
    INVALID_CHAN = -5,
    OFFSET_ERR = -6,
    READ_ERR = -7,
    CONVERTER_ERR = -8
};

int ceammc_coreaudio_getinfo(const char* path, audiofile_info_t* info);
int64_t ceammc_coreaudio_load(const char* path, size_t channel, size_t offset, size_t count, t_word* buf);

#if defined(__cplusplus)
}
#endif

#endif // CEAMMC_LOADER_COREAUDIO_IMPL_H
