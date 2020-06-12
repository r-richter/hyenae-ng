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
#include "../../../include/model/data_transformation/to_crc32_checksum.h"

#include <cstdlib>
#include <cstring>

namespace hyenae::model::data_transformations
{
    /*---------------------------------------------------------------------- */

    to_crc32_checksum::to_crc32_checksum(uint32_t polynomial)
    {
        _polynomial = polynomial;

    } /* to_crc32_checksum */

    /*---------------------------------------------------------------------- */

    size_t to_crc32_checksum::result_size(size_t data_size) const
    {
        return sizeof(uint32_t);

    } /* result_size */

    /*---------------------------------------------------------------------- */

    byte_t* to_crc32_checksum::transform(byte_t* data, size_t size) const
    {
        byte_t* result = NULL;
        size_t result_size = 0;
        uint32_t checksum = 0;

        assert::argument_not_null(data, "data");

        checksum = this->checksum(data, size);
        result_size = this->result_size(size);
        
        result = (byte_t*) malloc(result_size);
        memset(result, 0, result_size);
        memcpy(result, &checksum, result_size);

        free(data);

        return result;

    } /* transform */

    /*---------------------------------------------------------------------- */

    uint32_t to_crc32_checksum::checksum(byte_t* data, size_t size) const
    {
        uint32_t result = 0xFFFFFFFF;

        for (size_t pos = 0; pos < size; pos++)
        {
            result ^= *((uint8_t*)(data + pos));

            for (uint32_t i = 0; i < 8; i++)
            {
                if (result & 1)
                {
                    result = (result >> 1) ^ _polynomial;
                }
                else
                {
                    result = result >> 1;
                }
            }
        }

        return ~result;

    } /* checksum */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::data_transformations */
