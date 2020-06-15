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

#ifndef FIXED_DATA_GENERATOR_H
#define FIXED_DATA_GENERATOR_H

#include "../data_generator.h"

namespace hyenae::model::generators
{
    /*---------------------------------------------------------------------- */

    class fixed_data_generator :
        public data_generator
    {
        private:
            byte_t* _data;
            size_t _size;
            bool _free_on_destruction = false;

        public:
            fixed_data_generator(uint8_t value);
            fixed_data_generator(uint16_t value);
            fixed_data_generator(uint32_t value);
            fixed_data_generator(uint64_t value);
            fixed_data_generator(const byte_t* data, size_t size, bool clone);
            ~fixed_data_generator();
            static fixed_data_generator* allocate_uint8();
            static fixed_data_generator* allocate_uint16();
            static fixed_data_generator* allocate_uint32();
            static fixed_data_generator* allocate_uint64();
            static fixed_data_generator* allocate(size_t size);
            void next(bool data_changed = true) {};
            void reset(bool data_changed = true) {};
            uint8_t get_uint8() const;
            uint16_t get_uint16() const;
            uint32_t get_uint32() const;
            uint64_t get_uint64() const;
            void set_uint8(uint8_t value);
            void set_uint16(uint16_t value);
            void set_uint32(uint32_t value);
            void set_uint64(uint64_t value);

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* fixed_data_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators */

#endif /* FIXED_DATA_GENERATOR_H */
