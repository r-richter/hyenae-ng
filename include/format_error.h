/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
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

#ifndef FORMAT_ERROR_H
#define FORMAT_ERROR_H

#include "common.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    class format_error :
        public runtime_error_t
    {
        public:
            format_error(const string_t& message)
                : format_error(message.c_str()) {}

            format_error(const char* message)
                : runtime_error(message) {}

    }; /* format_error */

    /*---------------------------------------------------------------------- */

} /* hyenae */

#endif /* FORMAT_ERROR_H */
