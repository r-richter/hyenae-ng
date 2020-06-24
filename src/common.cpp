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

#include "../include/common.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    int64_t to_ms(duration_t duration)
    {
        return
            std::chrono::duration_cast<std::chrono::milliseconds>(
                duration).count();

    } /* to_ms */

    /*---------------------------------------------------------------------- */

    string_t to_ms_string(duration_t duration)
    {
        string_t text = "";

        text.append(std::to_string(to_ms(duration)));
        text.append(" ms");
        
        return text;

    } /* to_ms_string */

    /*---------------------------------------------------------------------- */

    // TODO: Refactor to va_list or remove
    string_t concat(string_t a, string_t b)
    {
        return a + b;

    } /* concat */

    /*---------------------------------------------------------------------- */

    string_t trim(const string_t& str)
    {
        string_t trimmed = str;

        trimmed = trim(trimmed, ' ');
        trimmed = trim(trimmed, '\t');
        trimmed = trim(trimmed, '\n');

        return trimmed;
    }

    /*---------------------------------------------------------------------- */

    string_t trim(const string_t& str, char chr)
    {
        string_t trimmed = str;

        while (trimmed.front() == chr)
        {
            trimmed = trimmed.substr(1);
        }

        while (trimmed.back() == chr)
        {
            trimmed = trimmed.substr(0, trimmed.size() - 1);
        }

        return trimmed;
    }

    /*---------------------------------------------------------------------- */

} /* hyenae */
