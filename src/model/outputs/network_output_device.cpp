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

#include "../../../include/assert.h"
#include "../../../include/os.h"
#include "../../../include/model/outputs/network_output.h"

#include <regex>

namespace hyenae::model::outputs
{
    /*---------------------------------------------------------------------- */

    network_output::device::device(const char* name, const char* description)
    {
        assert::argument_not_null((void*)name, "name");

        _name = name;

        if (description != NULL)
        {
            _description = description;

            #ifdef OS_WINDOWS
                _description = std::regex_replace(
                    _description, std::regex("\\Network adapter '"), "");
                _description = std::regex_replace(
                    _description, std::regex("\\' on local host"), "");
            #endif
        }
        else
        {
            _description = _name;
        }

    } /* device */

    /*---------------------------------------------------------------------- */

    string_t network_output::device::get_name() const
    {
        return _name;

    } /* get_name */

    /*---------------------------------------------------------------------- */

    string_t network_output::device::get_description() const
    {
        return _description;

    } /* get_description */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::outputs */
