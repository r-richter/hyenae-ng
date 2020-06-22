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

#include "../include/config.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    config::value::value(const string_t& name, const string_t& value)
    {
        _name = name;
        _value = value;

    } /* value */

    /*---------------------------------------------------------------------- */

    string_t config::value::get_name() const
    {
        return _name;

    } /* value */

    /*---------------------------------------------------------------------- */

    string_t config::value::get_value() const
    {
        return _value;

    } /* value */

    /*---------------------------------------------------------------------- */

    void config::value::set_value(const string_t& value)
    {
        _value = value;

    } /* set_value */

    /*---------------------------------------------------------------------- */

    string_t config::value::to_string() const
    {
        string_t value = "";
        value.append(_name);
        value.push_back(config::VALUE_ASSIGNER);
        value.append(_value);
        value.push_back(config::VALUE_DELIMITER);

        return value;

    } /* to_string */

    /*---------------------------------------------------------------------- */

} /* hyenae */
