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
#include "ceammc_loader_sndfile.h"

#include <iostream>

namespace ceammc {

namespace sound {

    LibSndFile::LibSndFile(const std::string& fname)
        : SoundFile(fname)
        , handle_(fname, SFM_READ, 0, 0, 0)
    {
        if (handle_.rawHandle() == 0) {
            std::cerr << "[SNDFILE] error while opening \"" << fname << "\": " << sf_strerror(0) << "\n";
        }
    }

    size_t LibSndFile::sampleCount() const
    {
        return handle_.frames();
    }

    size_t LibSndFile::sampleRate() const
    {
        return handle_.samplerate();
    }

    size_t LibSndFile::channels() const
    {
        return handle_.channels();
    }

    bool LibSndFile::isOpened() const
    {
        return handle_.rawHandle() != NULL;
    }

    bool LibSndFile::close()
    {
        handle_ = SndfileHandle();
        return true;
    }

    long LibSndFile::read(t_word* dest, size_t sz, size_t ch, long offset)
    {
        if (!handle_)
            return -1;

        if (ch >= channels())
            return -1;

        t_word* x = dest;
        const sf_count_t frame_count = 256;
        const int n = channels();
        const sf_count_t buf_size = frame_count * n;
        float frame_buf[buf_size];

        // move to beginning
        if (handle_.seek(offset, SEEK_SET) == -1)
            return -1;

        // read frames
        sf_count_t frames_read = 0;
        sf_count_t frames_read_total = 0;
        const sf_count_t steps = sf_count_t(sz) / frame_count;
        // read full buffers
        for (sf_count_t i = 0; i < steps; i++) {
            frames_read = handle_.readf(frame_buf, frame_count);
            if (frames_read == 0)
                break;

            frames_read_total += frames_read;

            // write channel data to destination
            for (sf_count_t j = 0; j < frames_read; j++) {
                x->w_float = frame_buf[j * n + ch];
                x++;
            }

            // seek to next
            if (handle_.seek(offset + frames_read_total, SEEK_SET) == -1)
                break;
        }

        // read remaining
        if (sf_count_t(sz) % frame_count != 0) {
            frames_read = handle_.readf(frame_buf, sf_count_t(sz) % frame_count);
            frames_read_total += frames_read;

            // write channel data to destination
            for (sf_count_t j = 0; j < frames_read; j++) {
                x->w_float = frame_buf[j * n + ch];
                x++;
            }
        }

        return frames_read_total;
    }

    FormatList LibSndFile::supportedFormats()
    {
        FormatList res;

        SF_FORMAT_INFO format_info;
        int count;
        sf_command(0, SFC_GET_FORMAT_MAJOR_COUNT, &count, sizeof(int));

        for (int k = 0; k < count; k++) {
            format_info.format = k;
            sf_command(0, SFC_GET_FORMAT_MAJOR, &format_info, sizeof(format_info));

            std::string finfo(format_info.name);
            std::string::size_type space_pos = finfo.find(' ', 0);
            std::string name = finfo.substr(0, space_pos);
            std::string desc = finfo.substr(space_pos + 0, std::string::npos);
            res.push_back(std::make_pair(name, desc));
        };

        return res;
    }
}
}
