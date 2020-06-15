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

#include "../../include/model/data_dispatcher.h"

namespace hyenae::model
{
    /*---------------------------------------------------------------------- */

    const duration_t data_dispatcher::limits::DURATION_UNLIMITED =
        duration_t{ 0 };

    /*---------------------------------------------------------------------- */

    data_dispatcher::limits::limits(
        size_t byte_limit, size_t packet_limit, duration_t duration_limit)
    {
        _byte_limit = byte_limit;
        _packet_limit = packet_limit;
        _duration_limit = duration_limit;

    } /* limits */

    /*---------------------------------------------------------------------- */

    bool data_dispatcher::limits::has_byte_limit() const
    {
        return _byte_limit != SIZE_UNLIMITED;

    } /* has_byte_limit */

    /*---------------------------------------------------------------------- */

    size_t data_dispatcher::limits::get_byte_limit() const
    {
        return _byte_limit;

    } /* get_byte_limit */

    /*---------------------------------------------------------------------- */

    bool data_dispatcher::limits::has_packet_limit() const
    {
        return _packet_limit != SIZE_UNLIMITED;

    } /* has_packet_limit */

    /*---------------------------------------------------------------------- */

    size_t data_dispatcher::limits::get_packet_limit() const
    {
        return _packet_limit;

    } /* get_packet_limit */

    /*---------------------------------------------------------------------- */

    bool data_dispatcher::limits::has_duration_limit() const
    {
        return _duration_limit != DURATION_UNLIMITED;

    } /* has_duration_limit */

    /*---------------------------------------------------------------------- */

    duration_t data_dispatcher::limits::get_duration_limit() const
    {
        return _duration_limit;

    } /* get_duration_limit */

    /*---------------------------------------------------------------------- */

} /* hyenae::model */
