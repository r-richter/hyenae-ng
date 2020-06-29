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
#include "../../../../include/model/generators/protocols/bootp_frame_generator.h"

namespace hyenae::model::generators::protocols
{
	/*---------------------------------------------------------------------- */

	bootp_frame_generator::bootp_frame_generator(
		uint8_t opcode,
		uint8_t hw_type,
		uint8_t hops,
		const string_t& transaction_id_pattern,
		size_t transaction_id_pattern_base,
		const string_t& seconds_pattern,
		size_t seconds_pattern_base,
		bool broadcast_flag,
		address_generator* client_ip_addr,
		address_generator* your_ip_addr,
		address_generator* server_ip_addr,
		address_generator* gateway_ip_addr,
		address_generator* client_hw_addr,
		const string_t& server_name,
		const string_t& file_name)
    {
        assert::argument_not_null(client_ip_addr, "client_ip_addr");
		assert::argument_not_null(your_ip_addr, "your_ip_addr");
		assert::argument_not_null(server_ip_addr, "server_ip_addr");
		assert::argument_not_null(gateway_ip_addr, "gateway_ip_addr");
		assert::argument_not_null(client_hw_addr, "client_hw_addr");

		assert::in_range(
			client_hw_addr->size() <= 16,
			"",
			"client hardware address exceeds 16 bit max");

		// Opcode
		_opcode = fixed_data_generator::allocate_uint8();
		_opcode->set_uint8(opcode);
		_packet.add_generator(_opcode);

		// HW-Type
		_hw_type = fixed_data_generator::allocate_uint8();
		_hw_type->set_uint8(hw_type);
		_packet.add_generator(_hw_type);

		// HW-Len
		_hw_len = fixed_data_generator::allocate_uint8();
		_hw_len->set_uint8((uint8_t)client_hw_addr->size());
		_packet.add_generator(_hw_len);

		// Hops
		_hops = fixed_data_generator::allocate_uint8();
		_hops->set_uint8(hops);
		_packet.add_generator(_hops);

        // Transaction ID
        _transaction_id = integer_generator::create_uint32(
            transaction_id_pattern, transaction_id_pattern_base);
        _transaction_id->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_transaction_id);

		// Seconds
        _seconds = integer_generator::create_uint16(
            seconds_pattern, seconds_pattern_base);
        _seconds->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_seconds);

		// Flags
		_flags = fixed_data_generator::allocate_uint16();
		_flags->set_uint16(broadcast_flag << 15);
		_packet.add_generator(_flags);

		// Client IP-Address
        _client_ip_addr = client_ip_addr;
        _packet.add_generator(_client_ip_addr);

		// Your IP-Address
        _your_ip_addr = your_ip_addr;
        _packet.add_generator(_your_ip_addr);

		// Server IP-Address
        _server_ip_addr = server_ip_addr;
        _packet.add_generator(_server_ip_addr);

		// Gateway IP-Address
        _gateway_ip_addr = gateway_ip_addr;
        _packet.add_generator(_gateway_ip_addr);

		// Client HW-Address
        _client_hw_addr = client_hw_addr;
        _packet.add_generator(_client_hw_addr);

		// Client HW-Address Padding
		if (_client_hw_addr->size() < 16)
		{

			_client_hw_addr_padding = fixed_data_generator::allocate(
				16 - _client_hw_addr->size());
			_packet.add_generator(_client_hw_addr_padding);
		}
		
		// Server Name
		_server_name = new fixed_data_generator(server_name, 64, 0);
		_packet.add_generator(_server_name);

		// File Name
		_file_name = new fixed_data_generator(file_name, 128, 0);
		_packet.add_generator(_file_name);

        // vendor
        _packet.add_generator(&_vendor);

    } /* bootp_frame_generator */

	/*---------------------------------------------------------------------- */

	bootp_frame_generator* bootp_frame_generator::create_for_ethernet(
		uint8_t opcode,
		uint8_t hops,
		const string_t& transaction_id_pattern,
		size_t transaction_id_pattern_base,
		const string_t& seconds_pattern,
		size_t seconds_pattern_base,
		bool broadcast_flag,
		const string_t& client_ip_pattern,
		const string_t& your_ip_pattern,
		const string_t& server_ip_pattern,
		const string_t& gateway_ip_pattern,
		const string_t& client_mac_pattern,
		const string_t& server_name,
		const string_t& file)
	{
		return new bootp_frame_generator(
			opcode,
			HW_TYPE_ETHERNET,
			hops,
			transaction_id_pattern,
			transaction_id_pattern_base,
			seconds_pattern,
			seconds_pattern_base,
			broadcast_flag,
			address_generator::create_ip_v4_address(
                client_ip_pattern,
                to_network_order_t::get_instance()),
			address_generator::create_ip_v4_address(
                your_ip_pattern,
                to_network_order_t::get_instance()),
			address_generator::create_ip_v4_address(
                server_ip_pattern,
                to_network_order_t::get_instance()),
			address_generator::create_ip_v4_address(
                gateway_ip_pattern,
                to_network_order_t::get_instance()),
			address_generator::create_mac_address(
                client_mac_pattern,
                to_network_order_t::get_instance()),
			server_name,
			file);

	} /* create_for_ethernet */

    /*---------------------------------------------------------------------- */

    bootp_frame_generator::~bootp_frame_generator()
    {
		safe_delete(_opcode);
		safe_delete(_hw_type);
		safe_delete(_hw_len);
		safe_delete(_hops);
		safe_delete(_transaction_id);
		safe_delete(_seconds);
		safe_delete(_flags);
		safe_delete(_client_ip_addr);
		safe_delete(_your_ip_addr);
		safe_delete(_server_ip_addr);
		safe_delete(_gateway_ip_addr);
		safe_delete(_client_hw_addr);
		safe_delete(_client_hw_addr_padding);
		safe_delete(_server_name);
		safe_delete(_file_name);
		safe_delete(_magic_cookie);

    } /* ~bootp_frame_generator */

    /*---------------------------------------------------------------------- */

    void bootp_frame_generator::next(bool data_changed)
    {
		_transaction_id->next(false);
		_seconds->next(false);
		_client_ip_addr->next(false);
		_your_ip_addr->next(false);
		_server_ip_addr->next(false);
		_gateway_ip_addr->next(false);
		_client_hw_addr->next(false);
		_vendor.next(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void bootp_frame_generator::reset(bool data_changed)
    {
		_transaction_id->reset(false);
		_seconds->reset(false);
		_client_ip_addr->reset(false);
		_your_ip_addr->reset(false);
		_server_ip_addr->reset(false);
		_gateway_ip_addr->reset(false);
		_client_hw_addr->reset(false);
		_vendor.reset(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* bootp_frame_generator::get_vendor()
    {
        return &_vendor;

    } /* get_vendor */

    /*---------------------------------------------------------------------- */

    size_t bootp_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* bootp_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
