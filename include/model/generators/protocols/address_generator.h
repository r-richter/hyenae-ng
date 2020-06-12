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

#ifndef ADDRESS_GENERATOR_H
#define ADDRESS_GENERATOR_H

#include "protocols.h"
#include "../../generator_group.h"
#include "../../data_transformation/to_network_order.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class address_generator :
        public data_generator
    {
        public:
            /* Bit sizes*/
            static const size_t BITS_OCTET = 8;
            static const size_t BITS_HEXTET = 16;

            /* Default patterns */
            static const string_t RAND_MAC_PATTERN;
            static const string_t RAND_IP_V4_PATTERN;
            static const string_t RAND_IP_V6_PATTERN;

        private:
            generator_group* _address;
            size_t _field_count;
            size_t _field_bits;
            size_t _base;

        public:
            address_generator(
                const string_t& pattern,
                size_t base,
                size_t field_count,
                size_t field_bits,
                char field_delimiter,
                data_transformation* field_transformation = NULL);

            ~address_generator();

            static address_generator* create_mac_address(
                const string_t& pattern = RAND_MAC_PATTERN,
                data_transformation* field_transformation = NULL);

            static address_generator* create_ipv4_address(
                const string_t& pattern = RAND_IP_V4_PATTERN,
                data_transformation* field_transformation = NULL);

            static address_generator* create_ipv6_address(
                const string_t& pattern = RAND_IP_V6_PATTERN,
                data_transformation* field_transformation = NULL);

            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            void to_mac_address(mac_address_t& result) const;
            void to_ipv4_address(ipv4_address_t& result) const;
            void to_ipv6_address(ipv6_address_t& result) const;

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

        private:
            static generator_group* parse_address(
                const string_t& pattern,
                size_t base,
                size_t field_count,
                size_t field_bits,
                char field_delimiter,
                data_transformation* field_transformation);

            static void free_address(generator_group* address);

    }; /* address_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* ADDRESS_GENERATOR_H */
