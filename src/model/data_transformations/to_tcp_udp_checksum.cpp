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

#include "../../../include/assert.h"
#include "../../../include/model/data_transformation/to_tcp_udp_checksum.h"

#include <cstring>

namespace hyenae::model::data_transformations
{
    /*---------------------------------------------------------------------- */

    to_tcp_udp_checksum* to_tcp_udp_checksum::_instance = NULL;

    /*---------------------------------------------------------------------- */

    to_tcp_udp_checksum* to_tcp_udp_checksum::get_instance()
    {
        if (_instance == NULL)
        {
            _instance = new to_tcp_udp_checksum();
        }

        return _instance;

    } /* get_instance */

    /*---------------------------------------------------------------------- */

    size_t to_tcp_udp_checksum::result_size(size_t data_size) const
    {
        return sizeof(uint16_t);

    } /* result_size */

    /*---------------------------------------------------------------------- */

    byte_t* to_tcp_udp_checksum::transform(byte_t* data, size_t size) const
    {
        byte_t* result = NULL;
        size_t result_size = 0;
        uint16_t checksum = 0;

        assert::argument_not_null(data, "data");

        checksum = this->checksum(data, size);
        result_size = this->result_size(size);

        result = (byte_t*)malloc(result_size);
        memset(result, 0, result_size);
        memcpy(result, &checksum, result_size);

        free(data);

        return result;

    } /* transform */

    /*---------------------------------------------------------------------- */

    uint16_t to_tcp_udp_checksum::checksum(byte_t* data, size_t size) const
    {
        unsigned long sum = 0;
        int tmp_size = size;

        while (tmp_size > 1)
        {
            sum += *((uint16_t*) data++);
            tmp_size -= sizeof(uint16_t);
        }

        if (tmp_size)
        {
            sum += *(unsigned char*)data;
        }

        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);

        return (uint16_t)(~sum);

    } /* checksum */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::data_transformations */
