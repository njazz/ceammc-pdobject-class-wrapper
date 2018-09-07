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
#include "ceammc_platform_win.h"

#include <Shlwapi.h>
#include <Stringapiset.h>
#include <Userenv.h>
#include <cstdlib>
#include <cstring>
#include <io.h>
#include <Windows.h>
#include <iostream>

#include "config.h"

#ifdef HAVE_LIBGEN_H
#include <libgen.h>
#endif

namespace ceammc {

bool win_is_path_relative(const char* path)
{
    return PathIsRelative(path) == 1;
}

std::string win_basename(const char* path)
{
#ifdef HAVE_LIBGEN_H
    char* p = strdup(path);
    char* bn = ::basename(p);
    if (!bn)
        return "";

    std::string res(bn);
    free(p);
    return res;
#else
    char* buf = strdup(path);
    PathStripPath(buf);
    std::string res(buf);
    free(buf);
    return res;
#endif
}

std::string win_dirname(const char* path)
{
#ifdef HAVE_LIBGEN_H
    char* p = strdup(path);
    char* dir = ::dirname(p);
    if (!dir)
        return "";

    std::string res(dir);
    free(p);
    return res;
#else
    char* buf = strdup(path);
    PathRemoveFileSpec(buf);
    std::string res(buf);
    free(buf);
    return res;
#endif
}

bool mb_to_wch(const char* str, wchar_t** res)
{
    int str_len = strlen(str) + 1;
    int wstr_len = MultiByteToWideChar(CP_UTF8, 0, str, str_len, 0, 0);
    if (wstr_len == 0)
        return false;

    wchar_t* wstr = static_cast<wchar_t*>(malloc(sizeof(wchar_t) * wstr_len));
    int rc = MultiByteToWideChar(CP_UTF8, 0, str, str_len, wstr, wstr_len);
    if (rc == 0) {
        free(wstr);
        return false;
    } else {
        *res = wstr;
        return true;
    }
}

bool win_fnmatch(const char* pattern, const char* str)
{
    wchar_t* wstr = 0;
    wchar_t* wpattern = 0;

    if (!mb_to_wch(str, &wstr) || !mb_to_wch(pattern, &wpattern))
        return false;

    BOOL res = PathMatchSpecW(wstr, wpattern);
    free(wstr);
    free(wpattern);
    return res;
}

bool win_path_exists(const char* path)
{
    wchar_t* wpath = 0;
    if (!mb_to_wch(path, &wpath))
        return false;

    BOOL res = PathFileExistsW(wpath);
    free(wpath);
    return res;
}

bool win_mkdir(const char* path, int flags)
{
    wchar_t* wpath = 0;
    if (!mb_to_wch(path, &wpath))
        return false;

    int err = _wmkdir(wpath);
    free(wpath);
    return err == 0;
}

bool win_rmdir(const char* path)
{
    wchar_t* wpath = 0;
    if (!mb_to_wch(path, &wpath))
        return false;

    int err = _wrmdir(wpath);
    free(wpath);
    return err == 0;
}

bool win_is_dir(const char* path)
{
    auto attrs = GetFileAttributesA(path);
    if(attrs == INVALID_FILE_ATTRIBUTES)
        return false;

    return attrs & FILE_ATTRIBUTE_DIRECTORY;
}

std::string win_home_directory()
{
    WCHAR buf[MAX_PATH] = { 0 };

    // We need a process with query permission set
    HANDLE token = 0;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
        return "";

    // Returns a path like C:/Documents and Settings/nibu if my user name is nibu
    DWORD buf_size = MAX_PATH;
    GetUserProfileDirectoryW(token, buf, &buf_size);
    CloseHandle(token);

    char* path;
    if (!wch_to_mb(buf, &path))
        return "";

    std::string home(path);
    free(path);
    return home;
}

bool wch_to_mb(const wchar_t* wstr, char** res)
{
    const int wstr_len = wcslen(wstr) + 1;
    int str_len = WideCharToMultiByte(CP_ACP, 0, wstr, wstr_len, 0, 0, 0, 0);
    if (str_len == 0)
        return false;

    char* str = static_cast<char*>(malloc(str_len));
    int rc = WideCharToMultiByte(CP_ACP, 0, wstr, wstr_len, str, str_len, 0, 0);
    if (!rc) {
        free(str);
        return false;
    } else {
        *res = str;
        return true;
    }
}

void win_sleep_ms(unsigned int ms)
{
    Sleep(ms);
}
}
