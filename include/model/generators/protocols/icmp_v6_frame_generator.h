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

#ifndef ICMP_V6_FRAME_GENERATOR_H
#define ICMP_V6_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../fixed_data_generator.h"
#include "../../data_transformation/to_network_order.h"
#include "../../data_transformation/to_internet_checksum.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class icmp_v6_frame_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

            using to_internet_checksum_t =
                data_transformations::to_internet_checksum;

        private:
            fixed_data_generator* _type = NULL;
            fixed_data_generator* _code = NULL;
            generator_group* _checksum = NULL;
            generator_group _payload;
            generator_group _packet;

        public:
            icmp_v6_frame_generator(
                data_generator* pseudo_header,
                uint8_t type = 0,
                uint8_t code = 0);

            ~icmp_v6_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            generator_group* get_payload();

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* icmp_v6_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* ICMP_V6_FRAME_GENERATOR_H */
