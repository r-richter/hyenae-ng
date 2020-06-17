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

#ifndef ARP_FRAME_GENERATOR_H
#define ARP_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../fixed_data_generator.h"
#include "../../data_transformation/to_network_order.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class arp_frame_generator :
        public data_generator
    {
        public:
            /* HW-Types */
            static const uint16_t HW_TYPE_ETHERNET = 1;

            /* Protocol-Types */
            static const uint16_t PROTO_TYPE_IP = 1;

            /* Operations */
            static const uint16_t OPERATION_REQUEST = 1;
            static const uint16_t OPERATION_REPLY = 2;

        private:
            using to_network_order_t =
                data_transformations::to_network_order;

        private:
            fixed_data_generator* _hw_addr_type = NULL;
            fixed_data_generator* _proto_addr_type = NULL;
            fixed_data_generator* _hw_addr_len = NULL;
            fixed_data_generator* _proto_addr_len = NULL;
            fixed_data_generator* _operation = NULL;
            address_generator* _sender_hw_addr = NULL;
            address_generator* _sender_proto_addr = NULL;
            address_generator* _target_hw_addr = NULL;
            address_generator* _target_proto_addr = NULL;
            generator_group _packet;

            arp_frame_generator(
                uint16_t hw_addr_type,
                uint16_t proto_addr_type,
                uint16_t operation,
                address_generator* sender_hw_addr,
                address_generator* sender_proto_addr,
                address_generator* target_hw_addr,
                address_generator* target_proto_addr);

        public:
            static arp_frame_generator* create_ip_v4_over_ethernet(
                uint16_t operation,
                const string_t& sender_mac_addr_pattern =
                    address_generator::RAND_MAC_PATTERN,
                const string_t& sender_ip_addr_pattern =
                    address_generator::RAND_IP_V4_PATTERN,
                const string_t& target_mac_addr_pattern =
                    address_generator::RAND_MAC_PATTERN,
                const string_t& target_ip_addr_pattern =
                    address_generator::RAND_IP_V4_PATTERN);

            ~arp_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* arp_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* ARP_FRAME_GENERATOR_H */
