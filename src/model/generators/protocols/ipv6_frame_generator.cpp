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

#include "../../../../include/assert.h"
#include "../../../../include/model/generators/protocols/ipv6_frame_generator.h"

#include <cstdlib>
#include <cstring>

namespace hyenae::model::generators::protocols
{
	/*---------------------------------------------------------------------- */

	ipv6_frame_generator::ipv6_frame_generator(
		uint8_t traffic_class,
		const string_t& flow_label_pattern,
		size_t flow_label_pattern_base,
		uint8_t next_header,
		uint8_t hop_limit,
		const string_t& src_ip_pattern,
		const string_t dst_ip_pattern)
	{
		// Version, Traffic class & Flow label
		_traffic_class = traffic_class;
		_flow_label = new integer_generator(
			flow_label_pattern, flow_label_pattern_base, 20);
		_version_traffic_flow = fixed_data_generator::allocate_uint32();
		_version_traffic_flow->add_transformation(
			to_network_order_t::get_instance());
		_packet.add_generator(_version_traffic_flow);
		
		// Payload length
		_payload_length_16bit = fixed_data_generator::allocate_uint16();
		_payload_length_16bit->add_transformation(
			to_network_order_t::get_instance());
		_payload_length_32bit = fixed_data_generator::allocate_uint32();
		_payload_length_32bit->add_transformation(
			to_network_order_t::get_instance());
		_packet.add_generator(_payload_length_16bit);
		
		// Next header
		_next_header = new fixed_data_generator(next_header);
		_packet.add_generator(_next_header);

		// Hop limit
		_hop_limit = new fixed_data_generator(hop_limit);
		_packet.add_generator(_hop_limit);

		// Source IP
		_src_ip_addr = address_generator::create_ipv6_address(
			src_ip_pattern, to_network_order_t::get_instance());
		_packet.add_generator(_src_ip_addr);

		// Destination IP
		_dst_ip_addr = address_generator::create_ipv6_address(
			dst_ip_pattern, to_network_order_t::get_instance());
		_packet.add_generator(_dst_ip_addr);

		// Payload
		_packet.add_generator(&_payload);

		// Pseudo-Header
		_reserved_24bit = fixed_data_generator::allocate(3);
		_pseudo_header.add_generator(_src_ip_addr);
		_pseudo_header.add_generator(_dst_ip_addr);
		_pseudo_header.add_generator(_payload_length_32bit);
		_pseudo_header.add_generator(_reserved_24bit);
		_pseudo_header.add_generator(_next_header);

		// Update fields
		update_version_traffic_flow();
		update_payload_length();

	} /* ipv6_frame_generator */

	/*---------------------------------------------------------------------- */

	ipv6_frame_generator::~ipv6_frame_generator()
	{
		safe_delete(_flow_label);
		safe_delete(_version_traffic_flow);
		safe_delete(_payload_length_16bit);
		safe_delete(_next_header);
		safe_delete(_hop_limit);
		safe_delete(_src_ip_addr);
		safe_delete(_dst_ip_addr);
		safe_delete(_reserved_24bit);
		safe_delete(_payload_length_32bit);

	} /* ~ipv6_frame_generator */

	/*---------------------------------------------------------------------- */

	void ipv6_frame_generator::next(bool data_changed)
	{
		_flow_label->next(false);
		_src_ip_addr->next(false);
		_dst_ip_addr->next(false);
		_payload.next();

		update_version_traffic_flow();
		update_payload_length();

		if (data_changed)
		{
			this->data_changed();
		}

	} /* next */

	/*---------------------------------------------------------------------- */

	void ipv6_frame_generator::reset(bool data_changed)
	{
		_flow_label->reset(false);
		_src_ip_addr->reset(false);
		_dst_ip_addr->reset(false);
		_payload.reset();

		update_version_traffic_flow();
		update_payload_length();

		if (data_changed)
		{
			this->data_changed();
		}

	} /* reset */

	/*---------------------------------------------------------------------- */

	generator_group* ipv6_frame_generator::get_payload()
	{
		return &_payload;

	} /* get_payload */

	/*---------------------------------------------------------------------- */

	data_generator* ipv6_frame_generator::get_pseudo_header() const
	{
		return (data_generator*)&_pseudo_header;

	} /* get_pseudo_header */

	/*---------------------------------------------------------------------- */

	size_t ipv6_frame_generator::data_size() const
	{
		return _packet.size();

	} /* data_size */

	/*---------------------------------------------------------------------- */

	byte_t* ipv6_frame_generator::data_to_buffer(
		byte_t* buffer, size_t size) const
	{
		return _packet.to_buffer(buffer, size);

	} /* data_to_buffer */

	/*---------------------------------------------------------------------- */

	void ipv6_frame_generator::update_payload_length()
	{
		_payload_length_16bit->set_uint16((uint16_t)_payload.size());
		_payload_length_32bit->set_uint32((uint16_t)_payload.size());

	} /* update_payload_length */

	/*---------------------------------------------------------------------- */

	void ipv6_frame_generator::update_version_traffic_flow()
	{
		_version_traffic_flow->set_uint32(
			(VERSION << 28) +
			(_traffic_class << 20) +
			_flow_label->get_uint32());

	} /* update_version_traffic_flow */

	/*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
