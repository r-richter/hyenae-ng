/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : hyenae.tool@googlemail.com
 *   Homepage : https://github.com/r-richter/hyenae-ng
 *
 * This file is part of Hyenae NG.
 *
 * Hyenae NG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hyenae NG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hyenae NG.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OS_H
#define OS_H

#if defined(_WIN32) || defined(_WIN64)
    #define OS_WINDOWS
#else
    #if defined(unix) || defined(__unix) || defined(__unix__) || defined(__FreeBSD__)
        #define OS_UNIX
    #elif defined(linux) || defined(__linux) || defined(__linux__)
        #define OS_LINUX
    #elif defined(__APPLE__) || defined(__MACH__)
        #define OS_OSX
    #endif

    #if defined(OS_UNIX) || defined(OS_LINUX) || defined(OS_OSX)
        #define OS_POSIX
    #else
        #error unknown os
    #endif
#endif

#endif /* OS_H */
