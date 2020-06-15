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

#include "../../../../include/assert.h"
#include "../../../../include/model/generators/protocols/ethernet_frame_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    ethernet_frame_generator::ethernet_frame_generator(
        bool add_preamble_sfd,
        const string_t& src_mac_pattern,
        const string_t& dst_mac_pattern,
        uint16_t type,
        bool add_fcs)
    {
        _to_crc32_checksum = new data_transformations::to_crc32_checksum(
            data_transformations::to_crc32_checksum::POLYNOMIAL_ETHERNET);

        // Preamble & SFD
        if (add_preamble_sfd)
        {
            _preamble_sfd = new fixed_data_generator(PREAMBLE_SFD);
            _packet.add_generator(_preamble_sfd);
        }
        
        // Source MAC
        _src_mac_addr = address_generator::create_mac_address(
            src_mac_pattern, to_network_order_t::get_instance());
        _packet.add_generator(_src_mac_addr);
        
        // Destination MAC
        _dst_mac_addr = address_generator::create_mac_address(
            dst_mac_pattern, to_network_order_t::get_instance());
        _packet.add_generator(_dst_mac_addr);

        // Type
        _type = new fixed_data_generator(type);
        _type->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_type);

        // Payload
        _packet.add_generator(&_payload);
        
        // FCS
        // Network order transformation does not have to be applied to the
        // checksum since the checksum itself is computed over the already
        // transformed data fields.
        if (add_fcs)
        {
            _fcs = new generator_group();
            _fcs->add_transformation(_to_crc32_checksum);
            _packet.add_generator(_fcs);

            // FCS targets

            if (add_preamble_sfd)
            {
                _fcs->add_generator(_preamble_sfd);
            }

            _fcs->add_generator(_src_mac_addr);
            _fcs->add_generator(_dst_mac_addr);
            _fcs->add_generator(_type);
            _fcs->add_generator(&_payload);
        }

    } /* ethernet_frame_generator */

    /*---------------------------------------------------------------------- */

    ethernet_frame_generator::~ethernet_frame_generator()
    {
        safe_delete(_preamble_sfd);
        safe_delete(_to_crc32_checksum);
        safe_delete(_src_mac_addr);
        safe_delete(_dst_mac_addr);
        safe_delete(_type);
        safe_delete(_fcs);

    } /* ~ethernet_frame_generator */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_generator::next(bool data_changed)
    {
        _src_mac_addr->next(false);
        _dst_mac_addr->next(false);
        _payload.next();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_generator::reset(bool data_changed)
    {
        _src_mac_addr->reset(false);
        _dst_mac_addr->reset(false);
        _payload.next();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* ethernet_frame_generator::get_payload()
    {
        return &_payload;

    } /* get_payload */

    /*---------------------------------------------------------------------- */

    size_t ethernet_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* ethernet_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
