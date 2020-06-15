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

#ifndef STRING_GENERATOR_H
#define STRING_GENERATOR_H

#include "../data_generator.h"

namespace hyenae::model::generators
{
    /*---------------------------------------------------------------------- */

    class string_generator :
        public data_generator
    {
        public:
            enum class encoding
            {
                ASCII = 1

            }; /* encoding */

        private:
            string_t _pattern;
            size_t _pattern_len;
            encoding _encoding;

        public:
            string_generator(const string_t& pattern, encoding encoding);
            void next(bool data_changed = true) {}
            void reset(bool data_changed = true) {}

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

        private:
            size_t data_size(encoding encoding) const;
            size_t char_size(char chr, encoding encoding) const;
            void ascii_data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* string_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators */

#endif /* STRING_GENERATOR_H */
