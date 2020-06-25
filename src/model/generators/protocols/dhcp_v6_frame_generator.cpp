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
#include "../../../../include/model/generators/protocols/dhcp_v6_frame_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

	dhcp_v6_frame_generator::dhcp_v6_frame_generator(
		uint8_t msg_type,
		const string_t& transaction_id_pattern,
		size_t transaction_id_pattern_base)
    {
		// Message Type
		_msg_type = fixed_data_generator::allocate_uint8();
		_msg_type->set_uint8(msg_type);
		_packet.add_generator(_msg_type);

		// Transaction-ID
		_transaction_id = new integer_generator(
			transaction_id_pattern, transaction_id_pattern_base, 24);
        _transaction_id->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_transaction_id);

        // Payload
        _packet.add_generator(&_payload);

    } /* dhcp_v6_frame_generator */

	/*---------------------------------------------------------------------- */

    dhcp_v6_frame_generator::~dhcp_v6_frame_generator()
    {
		safe_delete(_msg_type);
		safe_delete(_transaction_id);

    } /* ~dhcp_v6_frame_generator */

    /*---------------------------------------------------------------------- */

    void dhcp_v6_frame_generator::next(bool data_changed)
    {
		_transaction_id->next(false);
		_payload.next(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void dhcp_v6_frame_generator::reset(bool data_changed)
    {
		_transaction_id->reset(false);
		_payload.reset(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* dhcp_v6_frame_generator::get_payload()
    {
        return &_payload;

    } /* get_payload */

    /*---------------------------------------------------------------------- */

    size_t dhcp_v6_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* dhcp_v6_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
