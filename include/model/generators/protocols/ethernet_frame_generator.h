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

#ifndef ETHERNET_FRAME_GENERATOR_H
#define ETHERNET_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../fixed_data_generator.h"
#include "../../data_transformation/to_network_order.h"
#include "../../data_transformation/to_crc32_checksum.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class ethernet_frame_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

            using to_crc32_checksum_t =
                data_transformations::to_crc32_checksum;

        public:
            uint64_t PREAMBLE_SFD =
                0b1010101010101010101010101010101010101010101010101010101010101011;

            /* Types */
            static const uint16_t TYPE_IP_V4 = 0x0800;
            static const uint16_t TYPE_IP_V6 = 0x86DD;

        private:
            fixed_data_generator* _preamble_sfd = NULL;
            to_crc32_checksum_t* _to_crc32_checksum = NULL;
            address_generator* _src_mac_addr = NULL;
            address_generator* _dst_mac_addr = NULL;
            fixed_data_generator* _type = NULL;
            generator_group* _fcs = NULL;
            generator_group _payload;
            generator_group _packet;

        public:
            ethernet_frame_generator(
                bool add_preamble_sfd = false,
                const string_t& src_mac_pattern =
                address_generator::RAND_MAC_PATTERN,
                const string_t& dst_mac_pattern =
                address_generator::RAND_MAC_PATTERN,
                uint16_t type = TYPE_IP_V4,
                bool add_fcs = false);

            ~ethernet_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            generator_group* get_payload();

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* ethernet_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* ETHERNET_FRAME_GENERATOR_H */
