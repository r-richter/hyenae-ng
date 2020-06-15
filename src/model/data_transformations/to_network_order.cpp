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

#include "../../../include/endian.h"
#include "../../../include/assert.h"
#include "../../../include/model/data_transformation/to_network_order.h"

namespace hyenae::model::data_transformations
{
    /*---------------------------------------------------------------------- */

    to_network_order* to_network_order::_instance = NULL;

    /*---------------------------------------------------------------------- */

    to_network_order* to_network_order::get_instance()
    {
        if (_instance == NULL)
        {
            _instance = new to_network_order();
        }

        return _instance;

    } /* get_instance */

    /*---------------------------------------------------------------------- */

    byte_t* to_network_order::transform(byte_t* data, size_t size) const
    {
        assert::known_endianess();
        assert::argument_not_null(data, "data");

        if (endian::is_little_endian())
        {
            return to_reverse_order::transform(data, size);
        }

        return data;

    } /* transform */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::data_transformations */
