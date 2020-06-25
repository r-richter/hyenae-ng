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

#include "../../../../include/assert.h"
#include "../../../../include/model/generators/protocols/icmp_v6_frame_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    icmp_v6_frame_generator::icmp_v6_frame_generator(
        data_generator* pseudo_header,
        uint8_t type,
        uint8_t code)
    {
        assert::argument_not_null(pseudo_header, "pseudo_header");

        // Type
        _type = fixed_data_generator::allocate_uint8();
        _type->set_uint8(type);
        _packet.add_generator(_type);

        // Type
        _code = fixed_data_generator::allocate_uint8();
        _code->set_uint8(code);
        _packet.add_generator(_code);

        // Checksum
        //
        // Network order transformation does not have to be applied to the
        // checksum since the checksum itself is computed over the already
        // transformed data fields.
        _checksum = new generator_group();
        _checksum->add_transformation(to_internet_checksum_t::get_instance());
        _packet.add_generator(_checksum);

        // Checksum targets
        _checksum->add_generator(pseudo_header);
        _checksum->add_generator(_type);
        _checksum->add_generator(_code);
        _checksum->add_generator(&_payload);

        // Payload
        _packet.add_generator(&_payload);

    } /* icmp_v6_frame_generator */

    /*---------------------------------------------------------------------- */

    icmp_v6_frame_generator::~icmp_v6_frame_generator()
    {
        safe_delete(_type);
        safe_delete(_code);
        safe_delete(_checksum);

    } /* ~icmp_v6_frame_generator */

    /*---------------------------------------------------------------------- */

    void icmp_v6_frame_generator::next(bool data_changed)
    {
        _payload.next(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void icmp_v6_frame_generator::reset(bool data_changed)
    {
        _payload.reset(false);
        
        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* icmp_v6_frame_generator::get_payload()
    {
        return &_payload;

    } /* get_payload */

    /*---------------------------------------------------------------------- */

    size_t icmp_v6_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* icmp_v6_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
