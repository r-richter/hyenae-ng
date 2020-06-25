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

#include "../../../include/assert.h"
#include "../../../include/model/generators/fixed_data_generator.h"

#include <cstdlib>
#include <cstring>

namespace hyenae::model::generators
{
    /*---------------------------------------------------------------------- */

    fixed_data_generator::fixed_data_generator(uint8_t value) :
        fixed_data_generator((byte_t*)&value, 1, true) {};

    fixed_data_generator::fixed_data_generator(uint16_t value) :
        fixed_data_generator((byte_t*)&value, 2, true) {};

    fixed_data_generator::fixed_data_generator(uint32_t value) :
        fixed_data_generator((byte_t*)&value, 4, true) {};

    fixed_data_generator::fixed_data_generator(uint64_t value) :
        fixed_data_generator((byte_t*)&value, 8, true) {};

    /*---------------------------------------------------------------------- */
    
    fixed_data_generator::fixed_data_generator(
        const string_t& text, size_t size, char pad_chr)
    {
        string_t padded = "";

        assert::in_range(size > 0, "size");
        assert::no_overflow(text.size() <= size);

        padded = text + string_t(size - text.size(), pad_chr);

        _data = (byte_t*)malloc(size);
        memset(_data, 0, size);
        memcpy(_data, padded.c_str(), size);

        _size = size;
        _free_on_destruction = true;

    } /* fixed_data_generator */

    /*---------------------------------------------------------------------- */

    fixed_data_generator::fixed_data_generator(
        const byte_t* data, size_t size, bool clone)
    {
        assert::argument_not_null((void*)data, "data");
        assert::in_range(size > 0, "size");

        if (clone)
        {
            _data = (byte_t*)malloc(size);
            memset(_data, 0, size);
            memcpy(_data, data, size);
        }
        else
        {
            _data = (byte_t*) data;
        }
        
        _size = size;
        _free_on_destruction = clone;

    } /* fixed_data_generator */

    /*---------------------------------------------------------------------- */

    fixed_data_generator::~fixed_data_generator()
    {
        if (_free_on_destruction)
        {
            free(_data);
        }
        
    } /* ~fixed_data_generator */

    /*---------------------------------------------------------------------- */

    fixed_data_generator* fixed_data_generator::allocate_uint8()
    {
        return allocate(SIZE_UINT8);

    } /* allocate_uint8 */

    /*---------------------------------------------------------------------- */

    fixed_data_generator* fixed_data_generator::allocate_uint16()
    {
        return allocate(SIZE_UINT16);

    } /* allocate_uint16 */

    /*---------------------------------------------------------------------- */

    fixed_data_generator* fixed_data_generator::allocate_uint32()
    {
        return allocate(SIZE_UINT32);

    } /* allocate_uint32 */

    /*---------------------------------------------------------------------- */

    fixed_data_generator* fixed_data_generator::allocate_uint64()
    {
        return allocate(SIZE_UINT64);

    } /* allocate_uint64 */

    /*---------------------------------------------------------------------- */

    fixed_data_generator* fixed_data_generator::allocate(size_t size)
    {
        byte_t* buffer = NULL;
        fixed_data_generator* generator = NULL;

        assert::in_range(size > 0, "size");

        buffer = (byte_t*) malloc(size);
        memset(buffer, 0, size);

        generator = new fixed_data_generator(buffer, size, false);
        generator->_free_on_destruction = true;

        return generator;

    } /* allocate */

    /*---------------------------------------------------------------------- */

    uint8_t fixed_data_generator::get_uint8() const
    {
        assert::no_overflow(size() == SIZE_UINT8);

        return *((uint8_t*)_data);

    } /* get_uint8 */

    /*---------------------------------------------------------------------- */

    uint16_t fixed_data_generator::get_uint16() const
    {
        assert::no_overflow(size() <= SIZE_UINT16);

        return *((uint16_t*)_data);

    } /* get_uint16 */

    /*---------------------------------------------------------------------- */

    uint32_t fixed_data_generator::get_uint32() const
    {
        assert::no_overflow(size() <= SIZE_UINT32);

        return *((uint32_t*)_data);

    } /* get_uint32 */

    /*---------------------------------------------------------------------- */

    uint64_t fixed_data_generator::get_uint64() const
    {
        assert::no_overflow(size() <= SIZE_UINT64);

        return *((uint64_t*)_data);

    } /* get_uint64 */

    /*---------------------------------------------------------------------- */

    void fixed_data_generator::set_uint8(uint8_t value)
    {
        assert::no_overflow(size() <= SIZE_UINT8);

        *((uint8_t*)_data) = value;

    } /* set_uint8 */

    /*---------------------------------------------------------------------- */

    void fixed_data_generator::set_uint16(uint16_t value)
    {
        assert::no_overflow(size() <= SIZE_UINT16);

        *((uint16_t*)_data) = value;

    } /* set_uint16 */

    /*---------------------------------------------------------------------- */

    void fixed_data_generator::set_uint32(uint32_t value)
    {
        assert::no_overflow(size() <= SIZE_UINT32);

        *((uint32_t*)_data) = value;

    } /* set_uint32 */

    /*---------------------------------------------------------------------- */

    void fixed_data_generator::set_uint64(uint64_t value)
    {
        assert::no_overflow(size() <= SIZE_UINT64);

        *((uint64_t*)_data) = value;

    } /* set_uint64 */

    /*---------------------------------------------------------------------- */

    size_t fixed_data_generator::data_size() const
    {
        return _size;

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* fixed_data_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        assert::no_overflow(size >= this->data_size());

        memset(buffer, 0, size);
        memcpy(buffer, _data, _size);

        return buffer;

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators */
