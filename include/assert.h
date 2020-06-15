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

#ifndef ASSERT_H
#define ASSERT_H

#include "common.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    class assert
    {
        private:
            assert() {}

        public:
            static void known_endianess();

            static void in_range(
                bool expression,
                string_t param_name = "",
                string_t message = "");

            static void no_overflow(
                bool expression,
                string_t param_name = "",
                string_t message = "");

            static void valid_format(
                bool expression,
                string_t param_name = "",
                string_t message = "");

            static void valid_argument(
                bool expression,
                string_t param_name = "",
                string_t message = "");

            static void argument_not_null(
                void* pointer,
                string_t param_name = "",
                string_t message = "");

            static void legal_call(
                bool expression,
                string_t param_name = "",
                string_t message = "");

            static void legal_state(
                bool expression,
                string_t param_name = "",
                string_t message = "");

            static void in_time(
                bool expression,
                string_t param_name = "",
                string_t message = "");

            static void in_time(
                func_t<bool()> expression,
                int64_t timeout_in_ms,
                string_t param_name = "",
                string_t message = "");

        private:
            static string_t build_message(
                string_t param_name,
                string_t message,
                string_t default_message);

    }; /* assert */

    /*---------------------------------------------------------------------- */

} /* hyenae */

#endif /* ASSERT_H */
