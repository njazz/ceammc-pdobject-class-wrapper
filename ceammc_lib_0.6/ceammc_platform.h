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
#ifndef CEAMMC_PLATFORM_H
#define CEAMMC_PLATFORM_H

#include <boost/optional.hpp>
#include <string>
#include <vector>

#include "m_pd.h"

/**
 * Platform dependent function realization
 */

namespace ceammc {
namespace platform {
    const char* platform_name();
    bool is_path_relative(const char* path);

    std::string basename(const char* path);
    std::string dirname(const char* path);
    std::string expandenv(const char* str);

    bool fnmatch(const char* pattern, const char* str);

    /**
     * @brief returns true if given path (file or directory) exists
     */
    bool path_exists(const char* path);

    /**
     * Creates empty directory
     * @param path - directory path
     * @param flags - access parameters flags, read, write, execute. See man mkdir.
     *                If *-1* create with default parameters: rwxrwxr-x
     * @return true on success, false on error
     * @see rmdir
     */
    bool mkdir(const char* path, int flags = -1);

    /**
     * Removes a directory file whose name is given by path.
     * The directory must not have any entries other than '.' and '..'
     * @param path - directory path
     * @return true on success, false on error
     * @see mkdir
     */
    bool rmdir(const char* path);

    /**
     * Removes specified file
     * @param path - path fo file
     * @see rmdir()
     * @return true on sucess, false on error
     */
    bool remove(const char* path);

    /**
     * Returns standart system home directory
     */
    std::string home_directory();

    /**
     * Returns standart Pd user directory:
     */
    std::string pd_user_directory();

    std::string expand_tilde_path(const std::string& path);

    std::string strip_extension(const std::string& name);

    /**
     * Search file in standard PureData locations and tries to open it.
     * @return On success returns full path to file, else returns empty string
     */
    std::string find_in_std_path(t_canvas* cnv, const char* path);

    /**
     * @brief make_path_with_canvas
     * @param cnv
     * @param path
     * @return
     */
    std::string make_abs_filepath_with_canvas(t_canvas* cnv, const std::string& path);

    /**
      * Search file in directory of external
      * @return On success returns full path to file, else returns empty string
      */
    std::string find_in_exernal_dir(t_object* obj, const char* path);

    /**
     * suspend thread execution for an interval measured in milliseconds
     * @param ms
     */
    void sleep_ms(unsigned int ms);

    typedef std::vector<std::string> StringList;
    typedef boost::optional<StringList> DirList;
    /**
     * @brief list_directory
     * @param path
     * @param pattern
     * @return boost::null on error (can't read directory)
     */
    DirList list_directory(const char* path, const char* pattern = "");

    /**
     * check if specified path exists and is directory
     * @return true on sucess
     */
    bool is_dir(const char* path);
}
}

#endif // CEAMMC_PLATFORM_H
