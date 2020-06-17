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
#include "../../../../include/model/generators/protocols/arp_frame_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    arp_frame_generator::arp_frame_generator(
        uint16_t hw_addr_type,
        uint16_t proto_addr_type,
        uint16_t operation,
        address_generator* sender_hw_addr,
        address_generator* sender_proto_addr,
        address_generator* target_hw_addr,
        address_generator* target_proto_addr)
    {
        assert::argument_not_null(sender_hw_addr, "sender_hw_addr");
        assert::argument_not_null(sender_proto_addr, "sender_proto_addr");
        assert::argument_not_null(target_hw_addr, "target_hw_addr");
        assert::argument_not_null(target_proto_addr, "target_proto_addr");

        assert::valid_argument(
            sender_hw_addr->size() == target_hw_addr->size(),
            "",
            "hardware addresses differ in length");

        assert::valid_argument(
            sender_proto_addr->size() == target_proto_addr->size(),
            "",
            "protocol addresses differ in length");

        // HW-Address Type
        _hw_addr_type = fixed_data_generator::allocate_uint16();
        _hw_addr_type->add_transformation(
            to_network_order_t::get_instance());
        _hw_addr_type->set_uint16(hw_addr_type);
        _packet.add_generator(_hw_addr_type);

        // Protocol-Address Type
        _proto_addr_type = fixed_data_generator::allocate_uint16();
        _proto_addr_type->add_transformation(
            to_network_order_t::get_instance());
        _proto_addr_type->set_uint16(proto_addr_type);
        _packet.add_generator(_proto_addr_type);

        // HW-Address Length
        _hw_addr_len = fixed_data_generator::allocate_uint8();
        _hw_addr_len->set_uint8(sender_hw_addr->size());
        _packet.add_generator(_hw_addr_len);

        // Protocol-Address Length
        _proto_addr_len = fixed_data_generator::allocate_uint8();
        _proto_addr_len->set_uint8(sender_proto_addr->size());
        _packet.add_generator(_proto_addr_len);

        // Operation
        _operation = fixed_data_generator::allocate_uint16();
        _operation->add_transformation(
            to_network_order_t::get_instance());
        _operation->set_uint16(operation);
        _packet.add_generator(_operation);

        // Sender HW-Address
        _sender_hw_addr = sender_hw_addr;
        _packet.add_generator(_sender_hw_addr);

        // Sender Protocol-Address
        _sender_proto_addr = sender_proto_addr;
        _packet.add_generator(_sender_proto_addr);

        // Target HW-Address
        _target_hw_addr = target_hw_addr;
        _packet.add_generator(_target_hw_addr);

        // Target Protocol-Address
        _target_proto_addr = target_proto_addr;
        _packet.add_generator(_target_proto_addr);

    } /* arp_frame_generator */

    /*---------------------------------------------------------------------- */

    arp_frame_generator* arp_frame_generator::create_ip_v4_over_ethernet(
        uint16_t operation,
        const string_t& sender_mac_addr_pattern,
        const string_t& sender_ip_addr_pattern,
        const string_t& target_mac_addr_pattern,
        const string_t& target_ip_addr_pattern)
    {
        return new arp_frame_generator(
            HW_TYPE_ETHERNET,
            PROTO_TYPE_IP,
            operation,
            address_generator::create_mac_address(
                sender_mac_addr_pattern,
                to_network_order_t::get_instance()),
            address_generator::create_ip_v4_address(
                sender_ip_addr_pattern,
                to_network_order_t::get_instance()),
            address_generator::create_mac_address(
                target_mac_addr_pattern,
                to_network_order_t::get_instance()),
            address_generator::create_ip_v4_address(
                target_ip_addr_pattern,
                to_network_order_t::get_instance()));

    } /* create_ip_v4_over_ethernet */

    /*---------------------------------------------------------------------- */

    arp_frame_generator::~arp_frame_generator()
    {
        safe_delete(_hw_addr_type);
        safe_delete(_proto_addr_type);
        safe_delete(_hw_addr_len);
        safe_delete(_proto_addr_len);
        safe_delete(_operation);
        safe_delete(_sender_hw_addr);
        safe_delete(_sender_proto_addr);
        safe_delete(_target_hw_addr);
        safe_delete(_target_proto_addr);

    } /* ~arp_frame_generator */

    /*---------------------------------------------------------------------- */

    void arp_frame_generator::next(bool data_changed)
    {
        _sender_hw_addr->next(false);
        _sender_proto_addr->next(false);
        _target_hw_addr->next(false);
        _target_proto_addr->next(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void arp_frame_generator::reset(bool data_changed)
    {
        _sender_hw_addr->reset(false);
        _sender_proto_addr->reset(false);
        _target_hw_addr->reset(false);
        _target_proto_addr->reset(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    size_t arp_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* arp_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
