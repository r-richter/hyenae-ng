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
#include "../../../../include/model/generators/protocols/icmp_echo_payload_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    icmp_echo_payload_generator::icmp_echo_payload_generator(
        string_t id_pattern,
        size_t id_pattern_base,
        string_t seq_num_pattern,
        size_t seq_num_pattern_base)
    {
        // Identification
        _id = integer_generator::create_uint16(id_pattern, id_pattern_base);
        _id->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_id);

        // Sequence Number
        _seq_num = integer_generator::create_uint16(
            seq_num_pattern, seq_num_pattern_base);
        _seq_num->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_seq_num);

    } /* icmp_echo_payload_generator */

    /*---------------------------------------------------------------------- */

    icmp_echo_payload_generator::~icmp_echo_payload_generator()
    {
        safe_delete(_id);
        safe_delete(_seq_num);

    } /* ~icmp_echo_payload_generator */

    /*---------------------------------------------------------------------- */

    void icmp_echo_payload_generator::next(bool data_changed)
    {
        _id->next(false);
        _seq_num->next(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void icmp_echo_payload_generator::reset(bool data_changed)
    {
        _id->reset();
        _seq_num->reset();
        
        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */
    
    /*---------------------------------------------------------------------- */

    size_t icmp_echo_payload_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* icmp_echo_payload_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
