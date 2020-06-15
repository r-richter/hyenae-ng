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

#ifndef ICMP_ECHO_PAYLOAD_GENERATOR_H
#define ICMP_ECHO_PAYLOAD_GENERATOR_H

#include "address_generator.h"
#include "../integer_generator.h"
#include "../../data_transformation/to_network_order.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class icmp_echo_payload_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

        public:
            /* ICMPv4 */
            static const uint8_t ICMP_V4_TYPE = 0;
            static const uint8_t ICMP_V4_CODE = 0;

            /* ICMPv6 */
            static const uint8_t ICMP_V6_TYPE = 128;
            static const uint8_t ICMP_V6_CODE = 0;

        private:
            integer_generator* _id = NULL;
            integer_generator* _seq_num = NULL;
            generator_group _packet;

        public:
            icmp_echo_payload_generator(
                string_t id_pattern = "*****",
                size_t id_pattern_base = 10,
                string_t seq_num_pattern = "*****",
                size_t seq_num_pattern_base = 10);

            ~icmp_echo_payload_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);

            protected:
                size_t data_size() const;
                byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* icmp_echo_payload_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* ICMP_ECHO_PAYLOAD_GENERATOR_H */
