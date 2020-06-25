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

#ifndef DHCP_V6_FRAME_GENERATOR_H
#define DHCP_V6_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../integer_generator.h"
#include "../fixed_data_generator.h"
#include "../../data_transformation/to_network_order.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class dhcp_v6_frame_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

        public:
            /* Ports */
            static const uint16_t SERVER_PORT = 547;
            static const uint16_t CLIENT_PORT = 546;

        private:
            fixed_data_generator* _msg_type = NULL;
            integer_generator* _transaction_id = NULL;
            generator_group _payload;
            generator_group _packet;

        public:
            dhcp_v6_frame_generator(
                uint8_t msg_type = 0,
                const string_t& transaction_id_pattern = "****",
                size_t transaction_id_pattern_base = 10);

            ~dhcp_v6_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            generator_group* get_payload();

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* dhcp_v6_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* DHCP_V6_FRAME_GENERATOR_H */
