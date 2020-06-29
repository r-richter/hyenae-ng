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

#ifndef BOOTP_FRAME_GENERATOR_H
#define BOOTP_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../integer_generator.h"
#include "../fixed_data_generator.h"
#include "../../data_transformation/to_network_order.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class bootp_frame_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

        public:
            /* Opcodes */
            static const uint8_t OPCODE_REQUEST = 1;
            static const uint8_t OPCODE_REPLY = 2;

            /* Hardware-Types */
            static const uint8_t HW_TYPE_ETHERNET = 1;
            static const uint8_t HW_TYPE_IEEE_802 = 6;
            static const uint8_t HW_TYPE_ARCNET = 7;
            
            /* Ports */
            static const uint16_t SERVER_PORT = 67;
            static const uint16_t CLIENT_PORT = 68;

        private:
            fixed_data_generator* _opcode = NULL;
            fixed_data_generator* _hw_type = NULL;
            fixed_data_generator* _hw_len = NULL;
            fixed_data_generator* _hops = NULL;
            integer_generator* _transaction_id = NULL;
            integer_generator* _seconds = NULL;
            fixed_data_generator* _flags = NULL;
            address_generator* _client_ip_addr = NULL;
            address_generator* _your_ip_addr = NULL;
            address_generator* _server_ip_addr = NULL;
            address_generator* _gateway_ip_addr = NULL;
            address_generator* _client_hw_addr = NULL;
            fixed_data_generator* _client_hw_addr_padding = NULL;
            fixed_data_generator* _server_name = NULL;
            fixed_data_generator* _file_name = NULL;
            generator_group _vendor;
            generator_group _packet;

        public:
            bootp_frame_generator(
                uint8_t opcode,
                uint8_t hw_type,
                uint8_t hops,
                const string_t& transaction_id_pattern,
                size_t transaction_id_pattern_base,
                const string_t& seconds_pattern,
                size_t seconds_pattern_base,
                bool broadcast_flag,
                address_generator* client_ip_pattern,
                address_generator* your_ip_pattern,
                address_generator* server_ip_pattern,
                address_generator* gateway_ip_pattern,
                address_generator* client_hw_pattern,
                const string_t& server_name,
                const string_t& file);

            static bootp_frame_generator* create_for_ethernet(
                uint8_t opcode = OPCODE_REQUEST,
                uint8_t hops = 0,
                const string_t& transaction_id_pattern = "****",
                size_t transaction_id_pattern_base = 10,
                const string_t& seconds_pattern = "****",
                size_t seconds_pattern_base = 10,
                bool broadcast_flag = false,
                const string_t& client_ip_pattern =
                    address_generator::RAND_IP_V4_PATTERN,
                const string_t& your_ip_pattern =
                    address_generator::RAND_IP_V4_PATTERN,
                const string_t& server_ip_pattern =
                    address_generator::RAND_IP_V4_PATTERN,
                const string_t& gateway_ip_pattern =
                    address_generator::RAND_IP_V4_PATTERN,
                const string_t& client_mac_pattern =
                    address_generator::RAND_MAC_PATTERN,
                const string_t& server_name = "",
                const string_t& file = "");

            ~bootp_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            generator_group* get_vendor();

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* bootp_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* BOOTP_FRAME_GENERATOR_H */
