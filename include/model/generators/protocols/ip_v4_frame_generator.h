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

#ifndef IP_V4_FRAME_GENERATOR_H
#define IP_V4_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../fixed_data_generator.h"
#include "../integer_generator.h"
#include "../../data_transformation/to_network_order.h"
#include "../../data_transformation/to_internet_checksum.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class ip_v4_frame_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

            using to_internet_checksum_t =
                data_transformations::to_internet_checksum;

        public:
            static const uint8_t VERSION = 4;
            static const uint8_t IHL = 5;

            /* Protocols */
            static const uint8_t PROTOCOL_TCP = 0x06;
            static const uint8_t PROTOCOL_UDP = 0x11;

        private:
            fixed_data_generator* _version_ihl = NULL;
            fixed_data_generator* _type_of_service = NULL;
            fixed_data_generator* _total_length = NULL;
            integer_generator* _id = NULL;
            bool _dont_frag;
            bool _more_frags;
            integer_generator* _frag_offset = NULL;
            fixed_data_generator* _flags_frag_offset = NULL;
            fixed_data_generator* _time_to_live = NULL;
            fixed_data_generator* _protocol = NULL;
            generator_group* _checksum;
            fixed_data_generator* _checksum_dummy = NULL;
            address_generator* _src_ip_addr = NULL;
            address_generator* _dst_ip_addr = NULL;
            fixed_data_generator* _reserved_8bit = NULL;
            fixed_data_generator* _payload_length = NULL;
            generator_group _payload;
            generator_group _packet;
            generator_group _pseudo_header;
            
        public:
            ip_v4_frame_generator(
                uint8_t type_of_service = 0, // TODO: Add TOS constants...
                const string_t& id_pattern = "*****",
                size_t id_pattern_base = 10,
                bool dont_frag = false,
                bool more_frags = false,
                const string_t& frag_offset_pattern = "0",
                size_t frag_offset_pattern_base = 10,
                uint8_t time_to_live = 128,
                uint8_t protocol = PROTOCOL_TCP,
                const string_t& src_ip_pattern =
                    address_generator::RAND_IP_V4_PATTERN,
                const string_t dst_ip_pattern =
                    address_generator::RAND_IP_V4_PATTERN);

            ~ip_v4_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            generator_group* get_payload();
            data_generator* get_pseudo_header() const;

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;
            void update_payload_length();
            void update_flags_frag_offset();

    }; /* ip_v4_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* IP_V4_FRAME_GENERATOR_H */
