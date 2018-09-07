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
#ifndef CEAMMC_PLATFORM_UNIX_H
#define CEAMMC_PLATFORM_UNIX_H

#include <string>

namespace ceammc {
bool unix_is_path_relative(const char* path);
std::string unix_basename(const char* path);
std::string unix_dirname(const char* path);
bool unix_fnmatch(const char* pattern, const char* str);
bool unix_path_exists(const char* path);
bool unix_mkdir(const char* path, int flags = -1);
bool unix_rmdir(const char* path);
std::string unix_home_directory();
void unix_sleep_ms(unsigned int ms);
bool unix_is_dir(const char* path);
}

#endif // CEAMMC_PLATFORM_UNIX_H
