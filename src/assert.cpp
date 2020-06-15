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

#include "../include/endian.h"
#include "../include/assert.h"
#include "../include/timeout.h"
#include "../include/stop_watch.h"
#include "../include/format_error.h"
#include "../include/illegal_call.h"
#include "../include/illegal_state.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    void assert::known_endianess()
    {
        if (endian::is_unknown_endianess())
        {
            throw runtime_error_t("unknown endianess");
        }

    } /* known_endianess */

    /*---------------------------------------------------------------------- */

    void assert::in_range(
        bool expression, string_t param_name, string_t message)
    {
        if (!expression)
        {
            throw std::out_of_range(
                build_message(param_name, message, "out of range"));
        }

    } /* in_range */

    /*---------------------------------------------------------------------- */

    void assert::no_overflow(
        bool expression, string_t param_name, string_t message)
    {
        if (!expression)
        {
            throw std::overflow_error(
                build_message(param_name, message, "overflow"));
        }

    } /* no_overflow */

    /*---------------------------------------------------------------------- */

    void assert::valid_format(
        bool expression, string_t param_name, string_t message)
    {
        if (!expression)
        {
            throw format_error(
                build_message(param_name, message, "invalid format"));
        }

    } /* valid_format */

    /*---------------------------------------------------------------------- */

    void assert::valid_argument(
        bool expression, string_t param_name, string_t message)
    {
        if (!expression)
        {
            throw std::invalid_argument(
                build_message(param_name, message, "invalid argument"));
        }

    } /* valid_argument */

    /*---------------------------------------------------------------------- */

    void assert::argument_not_null(
        void* pointer, string_t param_name, string_t message)
    {
        valid_argument(
            pointer != NULL, param_name, message != "" ? message : "is null");

    } /* argument_not_null */

    /*---------------------------------------------------------------------- */

    void assert::legal_call(
        bool expression, string_t param_name, string_t message)
    {
        if (!expression)
        {
            throw illegal_call(
                build_message(param_name, message, "illegal call"));
        }

    } /* legal_call */

    /*---------------------------------------------------------------------- */

    void assert::legal_state(
        bool expression, string_t param_name, string_t message)
    {
        if (!expression)
        {
            throw illegal_state(
                build_message(param_name, message, "illegal state"));
        }

    } /* legal_state */

    /*---------------------------------------------------------------------- */

    void assert::in_time(
        bool expression, string_t param_name, string_t message)
    {
        if (!expression)
        {
            throw std::out_of_range(
                build_message(param_name, message, "timeout"));
        }

    } /* in_time */

    /*---------------------------------------------------------------------- */

    void assert::in_time(
        func_t<bool()> expression,
        int64_t timeout_in_ms,
        string_t param_name,
        string_t message)
    {
        stop_watch timeout_watch;

        timeout_watch.start();

        while (to_ms(timeout_watch.get_time_passed()) < timeout_in_ms)
        {
            if (expression())
            {
                return;
            }
        }

        assert::in_time(false, param_name, message);
    }

    /*---------------------------------------------------------------------- */

    string_t assert::build_message(
        string_t param_name, string_t message, string_t default_message)
    {
        return
            param_name +
            (param_name != "" ? ": " : "") +
            (message != "" ? message : default_message);

    } /* build_message */

    /*---------------------------------------------------------------------- */

} /* hyenae */
