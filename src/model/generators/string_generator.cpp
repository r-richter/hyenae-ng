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

#include "../../../include/assert.h"
#include "../../../include/model/generators/string_generator.h"

#include <cstdlib>
#include <cstring>

namespace hyenae::model::generators
{
    /*---------------------------------------------------------------------- */

    string_generator::string_generator(
        const string_t& pattern, encoding encoding)
    {
        _pattern = pattern;
        _pattern_len = pattern.size();
        _encoding = encoding;

    } /* string_generator */

    /*---------------------------------------------------------------------- */

    size_t string_generator::data_size() const
    {
        return data_size(_encoding);

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* string_generator::data_to_buffer(byte_t* buffer, size_t size) const
    {
        assert::no_overflow(size >= this->data_size());

        switch (_encoding)
        {
            case encoding::ASCII:
                ascii_data_to_buffer(buffer, size);
                break;

            default:
                assert::in_range(false, "encoding", "unknown encoding");
        }

        return buffer;

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

    size_t string_generator::data_size(encoding encoding) const
    {
        size_t size = 0;

        for (char chr : _pattern)
        {
            size += char_size(chr, encoding);
        }

        return size;

    } /* data_size */

    /*---------------------------------------------------------------------- */

    size_t string_generator::char_size(char chr, encoding encoding) const
    {
        switch (encoding)
        {
            case encoding::ASCII:
                return 1;

            default:
                assert::in_range(false, "encoding", "unknown encoding");
        }

        return SIZE_NONE;

    } /* char_size */

    /*---------------------------------------------------------------------- */

    void string_generator::ascii_data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        memset(buffer, 0, size);
        memcpy(buffer, _pattern.c_str(), size);

    } /* ascii_data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators */
