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

#ifndef IPV6_FRAME_GENERATOR_H
#define IPV6_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../fixed_data_generator.h"
#include "../integer_generator.h"
#include "../../data_transformation/to_network_order.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class ipv6_frame_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

        public:
            static const uint8_t VERSION = 6;

            /* Next header */
            static const uint8_t NEXT_HEADER_TCP = 0x06;
            static const uint8_t NEXT_HEADER_UDP = 0x11;

        private:
            uint8_t _traffic_class;
            integer_generator* _flow_label = NULL;
            fixed_data_generator* _version_traffic_flow = NULL;
            fixed_data_generator* _payload_length_16bit = NULL;
            fixed_data_generator* _next_header = NULL;
            fixed_data_generator* _hop_limit = NULL;
            address_generator* _src_ip_addr = NULL;
            address_generator* _dst_ip_addr = NULL;
            fixed_data_generator* _reserved_24bit = NULL;
            fixed_data_generator* _payload_length_32bit = NULL;
            generator_group _payload;
            generator_group _packet;
            generator_group _pseudo_header;

        public:
            ipv6_frame_generator(
                uint8_t traffic_class = 0,
                const string_t& flow_label_pattern = "*****",
                size_t flow_label_pattern_base = 10,
                uint8_t next_header = NEXT_HEADER_TCP,
                uint8_t hop_limit = 128,
                const string_t& src_ip_pattern =
                    address_generator::RAND_IP_V6_PATTERN,
                const string_t dst_ip_pattern =
                    address_generator::RAND_IP_V6_PATTERN);

            ~ipv6_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            generator_group* get_payload();
            data_generator* get_pseudo_header() const;

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;
            void update_payload_length();
            void update_version_traffic_flow();

    }; /* ipv6_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* IPV6_FRAME_GENERATOR_H */
