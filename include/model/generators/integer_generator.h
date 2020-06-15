/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
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

#ifndef INTEGER_GENERATOR_H
#define INTEGER_GENERATOR_H

#include "../data_generator.h"

namespace hyenae::model::generators
{
    /*---------------------------------------------------------------------- */

    class integer_generator :
        public data_generator
    {
        public:
            /* Bases */
            static const size_t BASE_BINARY = 2;
            static const size_t BASE_OCTAL = 8;
            static const size_t BASE_DECIMAL = 10;
            static const size_t BASE_HEXADECIMAL = 16;
            static const size_t BASE_MIN = BASE_BINARY;
            static const size_t BASE_MAX = BASE_HEXADECIMAL;

            /* Bit sizes*/
            static const size_t BITS_UINT8 = 8;
            static const size_t BITS_UINT16 = 16;
            static const size_t BITS_UINT32 = 32;
            static const size_t BITS_UINT64 = 64;
            static const size_t BITS_MIN = 1;
            static const size_t BITS_MAX = BITS_UINT64;

            /* Wildcards */
            static const char RAND_WILDCARD = '*';
            static const char INCR_WILDCARD = '+';
            static const char DECR_WILDCARD = '-';

        private:
            static const char* BASE_CHARS;
            string_t _pattern;
            size_t _pattern_len;
            size_t _base;
            size_t _bits;
            uint64_t _result_min;
            uint64_t _result_max;
            uint64_t _result;
            uint64_t _offset;

        public:
            integer_generator(
                const string_t& pattern, size_t base, size_t bits);

            static integer_generator* create_uint8(
                const string_t& pattern, size_t base);

            static integer_generator* create_uint16(
                const string_t& pattern, size_t base);

            static integer_generator* create_uint32(
                const string_t& pattern, size_t base);

            static integer_generator* create_uint64(
                const string_t& pattern, size_t base);

            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            uint8_t get_uint8() const;
            uint16_t get_uint16() const;
            uint32_t get_uint32() const;
            uint64_t get_uint64() const;

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;
            
        private:
            static uint64_t int_max(size_t bits);
            static size_t bit_to_byte_size(size_t bits);
            static uint8_t chr_value(char chr, size_t base);
            static void validate_format(const string_t& pattern, size_t base);

            static uint64_t digit_value(
                uint64_t value, size_t base, size_t pos);

            static uint64_t replace_wildcards(
                const string_t& pattern,
                size_t base,
                size_t value,
                uint64_t max);

            uint64_t result_min(uint64_t max) const;
            uint64_t result_max(uint64_t max) const;
            uint64_t result() const;

    }; /* integer_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators */

#endif /* INTEGER_GENERATOR_H */
