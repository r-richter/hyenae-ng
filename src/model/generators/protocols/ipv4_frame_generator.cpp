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

#include "../../../../include/model/generators/protocols/ipv4_frame_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    ipv4_frame_generator::ipv4_frame_generator(
        uint8_t type_of_service,
        const string_t& id_pattern,
        size_t id_pattern_base,
        bool dont_frag,
        bool more_frags,
        const string_t& frag_offset_pattern,
        size_t frag_offset_pattern_base,
        uint8_t time_to_live,
        uint8_t protocol,
        const string_t& src_ip_pattern,
        const string_t dst_ip_pattern)
    {
        // Version & IHL
        _version_ihl = new fixed_data_generator(
            (uint8_t) ((VERSION << 4) + IHL));
        _packet.add_generator(_version_ihl);

        // Type of service
        _type_of_service = new fixed_data_generator(type_of_service);
        _packet.add_generator(_type_of_service);

        // Total length / Payload Length
        _total_length = fixed_data_generator::allocate_uint16();
        _total_length->add_transformation(to_network_order_t::get_instance());
        _payload_length = fixed_data_generator::allocate_uint16();
        _payload_length->add_transformation(
            to_network_order_t::get_instance());
        _packet.add_generator(_total_length);
        
        // Identification
        _id = integer_generator::create_uint16(id_pattern, id_pattern_base);
        _id->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_id);

        // Flags & Fragmentation offset
        _dont_frag = dont_frag;
        _more_frags = more_frags;
        _frag_offset= new integer_generator(
            frag_offset_pattern, frag_offset_pattern_base, 13);
        _flags_frag_offset = fixed_data_generator::allocate_uint16();
        _flags_frag_offset->add_transformation(
            to_network_order_t::get_instance());
        _packet.add_generator(_flags_frag_offset);
        
        // Time to live
        _time_to_live = new fixed_data_generator(time_to_live);
        _packet.add_generator(_time_to_live);

        // Protocol
        _protocol = new fixed_data_generator(protocol);
        _packet.add_generator(_protocol);

        // Checksum
        //
        // Network order transformation does not have to be applied to the
        // checksum since the checksum itself is computed over the already
        // transformed data fields.
        _checksum = new generator_group();
        _checksum->add_transformation(to_internet_checksum_t::get_instance());
        _packet.add_generator(_checksum);

        // Source IP
        _src_ip_addr = address_generator::create_ipv4_address(
            src_ip_pattern, to_network_order_t::get_instance());
        _packet.add_generator(_src_ip_addr);

        // Destination IP
        _dst_ip_addr = address_generator::create_ipv4_address(
            dst_ip_pattern, to_network_order_t::get_instance());
        _packet.add_generator(_dst_ip_addr);

        // Payload
        _packet.add_generator(&_payload);

        // Checksum targets
        _checksum_dummy = fixed_data_generator::allocate_uint16();
        _checksum->add_generator(_version_ihl);
        _checksum->add_generator(_type_of_service);
        _checksum->add_generator(_total_length);
        _checksum->add_generator(_id);
        _checksum->add_generator(_flags_frag_offset);
        _checksum->add_generator(_time_to_live);
        _checksum->add_generator(_protocol);
        _checksum->add_generator(_checksum_dummy);
        _checksum->add_generator(_src_ip_addr);
        _checksum->add_generator(_dst_ip_addr);

        // Pseudo-Header
        _reserved_8bit = fixed_data_generator::allocate_uint8();
        _pseudo_header.add_generator(_src_ip_addr);
        _pseudo_header.add_generator(_dst_ip_addr);
        _pseudo_header.add_generator(_reserved_8bit);
        _pseudo_header.add_generator(_protocol);
        _pseudo_header.add_generator(_payload_length);

        // Update fields
        update_flags_frag_offset();
        update_payload_length();

    } /* ipv4_frame_generator */

    /*---------------------------------------------------------------------- */

    ipv4_frame_generator::~ipv4_frame_generator()
    {
        safe_delete(_version_ihl);
        safe_delete(_type_of_service);
        safe_delete(_total_length);
        safe_delete(_id);
        safe_delete(_frag_offset);
        safe_delete(_flags_frag_offset);
        safe_delete(_time_to_live);
        safe_delete(_protocol);
        safe_delete(_checksum);
        safe_delete(_checksum_dummy);
        safe_delete(_src_ip_addr);
        safe_delete(_dst_ip_addr);
        safe_delete(_reserved_8bit);
        safe_delete(_payload_length);

    } /* ~ipv4_frame_generator */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_generator::next(bool data_changed)
    {
        _frag_offset->next(false);
        _id->next(false);
        _src_ip_addr->next(false);
        _dst_ip_addr->next(false);
        _payload.next();

        update_payload_length();
        update_flags_frag_offset();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_generator::reset(bool data_changed)
    {
        _frag_offset->reset(false);
        _id->reset(false);
        _src_ip_addr->reset(false);
        _dst_ip_addr->reset(false);
        _payload.reset();

        update_payload_length();
        update_flags_frag_offset();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* ipv4_frame_generator::get_payload()
    {
        return &_payload;

    } /* get_payload */

    /*---------------------------------------------------------------------- */

    data_generator* ipv4_frame_generator::get_pseudo_header() const
    {
        return (data_generator*)&_pseudo_header;

    } /* get_pseudo_header */

    /*---------------------------------------------------------------------- */

    size_t ipv4_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* ipv4_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_generator::update_payload_length()
    {
        _total_length->set_uint16(
            (uint16_t)((IHL * 4) + _payload.size()));

        _payload_length->set_uint16((uint16_t)_payload.size());

    } /* update_payload_length */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_generator::update_flags_frag_offset()
    {
        _flags_frag_offset->set_uint16(
            (_dont_frag << 14) +
            (_more_frags << 13) +
            _frag_offset->get_uint16());

    } /* update_flags_frag_offset */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
