/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
 *   Homepage : http://sourceforge.net/projects/hyenae-ng/
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

#ifndef COMMON_H
#define COMMON_H

#include <cstddef>
#include <cstdint>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cstring>
#include <cstdarg>
#include <stdexcept>
#include <functional>

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    /* Sizes */

    static const size_t SIZE_UINT8 = 1;
    static const size_t SIZE_UINT16 = 2;
    static const size_t SIZE_UINT32 = 4;
    static const size_t SIZE_UINT64 = 8;

    static const size_t FORMAT_BUFFER_SIZE = 1024;

    /*---------------------------------------------------------------------- */

    /* Types */

    using byte_t = std::byte;
    using thread_t = std::thread;
    using string_t = std::string;
    using duration_t = std::chrono::system_clock::duration;

    template<typename T>
    using func_t = std::function<T>;

    template<typename T>
    using vector_t = std::vector<T>;

    template<typename K, typename V>
    using unordered_map_t = std::unordered_map<K, V>;

    using exception_t = std::exception;
    using runtime_error_t = std::runtime_error;

    /*---------------------------------------------------------------------- */

    /* Methods */

    template< class T >
    void safe_delete(T*& ptr)
    {
        if (ptr != NULL)
        {
            delete ptr;
            ptr = NULL;
        }

    } /* safe_delete */ 
    
    int64_t to_ms(duration_t duration);

    string_t to_ms_string(duration_t duration);

    string_t concat(string_t a, string_t b);

    /*---------------------------------------------------------------------- */

} /* hyenae */

#endif /* COMMON_H */
