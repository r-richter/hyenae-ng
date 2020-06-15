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

#include "../../../include/assert.h"
#include "../../../include/model/generators/integer_generator.h"

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>

namespace hyenae::model::generators
{
    /*---------------------------------------------------------------------- */

    const char* integer_generator::BASE_CHARS = "0123456789abcdef";

    /*---------------------------------------------------------------------- */

    integer_generator::integer_generator(
        const string_t& pattern, size_t base, size_t bits)
    {
        uint64_t max = int_max(bits);

        assert::in_range(base >= BASE_MIN && base <= BASE_MAX, "base");
        assert::in_range(bits >= BITS_MIN && bits <= BITS_MAX, "bits");
        assert::no_overflow(base <= (max + 1), "base", "int max exceeded");
        validate_format(pattern, base);
        assert::no_overflow(replace_wildcards(
            pattern, base, 1, max) <= max, "pattern", "int max exceeded");

        _pattern = pattern;
        _base = base;
        _bits = bits;

        max = int_max(bits);

        _pattern_len = pattern.size();
        _result_min = result_min(max);
        _result_max = result_max(max);

        srand((unsigned int)time(NULL));

        reset(false);

    } /* integer_generator */

    /*---------------------------------------------------------------------- */

    integer_generator* integer_generator::create_uint8(
        const string_t& pattern, size_t base)
    {
        return new integer_generator(pattern, base, BITS_UINT8);

    } /* create_uint8 */

    /*---------------------------------------------------------------------- */

    integer_generator* integer_generator::create_uint16(
        const string_t& pattern, size_t base)
    {
        return new integer_generator(pattern, base, BITS_UINT16);

    } /* create_uint16 */

    /*---------------------------------------------------------------------- */

    integer_generator* integer_generator::create_uint32(
        const string_t& pattern, size_t base)
    {
        return new integer_generator(pattern, base, BITS_UINT32);

    } /* create_uint32 */

    /*---------------------------------------------------------------------- */

    integer_generator* integer_generator::create_uint64(
        const string_t& pattern, size_t base)
    {
        return new integer_generator(pattern, base, BITS_UINT64);

    } /* create_uint64 */

    /*---------------------------------------------------------------------- */

    void integer_generator::next(bool data_changed)
    {
        // Since the calculation of an offset max value (number of possible
        // steps based on the given pattern) would be the same procedure as
        // for generating the actual result value, we will generate the result
        // value first instead and reset if neccessary.

        _offset++;

        _result = result();

        if (_result < _result_min)
        {
            _result = _result_max;

            _offset = 0;
        }
        else if (_result > _result_max)
        {
            _result = _result_min;

            _offset = 0;
        }

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void integer_generator::reset(bool data_changed)
    {
        _offset = 0;
        _result = _result_min;

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    uint8_t integer_generator::get_uint8() const
    {
        uint8_t result = 0;

        assert::no_overflow(size() == SIZE_UINT8);

        to_buffer((byte_t*) &result, size());

        return result;

    } /* get_uint8 */

    /*---------------------------------------------------------------------- */

    uint16_t integer_generator::get_uint16() const
    {
        uint16_t result = 0;

        assert::no_overflow(size() <= SIZE_UINT16);

        to_buffer((byte_t*)&result, size());

        return result;

    } /* get_uint16 */

    /*---------------------------------------------------------------------- */

    uint32_t integer_generator::get_uint32() const
    {
        uint32_t result = 0;

        assert::no_overflow(size() <= SIZE_UINT32);

        to_buffer((byte_t*)&result, size());

        return result;

    } /* get_uint32 */

    /*---------------------------------------------------------------------- */

    uint64_t integer_generator::get_uint64() const
    {
        uint64_t result = 0;

        assert::no_overflow(size() <= SIZE_UINT64);

        to_buffer((byte_t*)&result, size());

        return result;

    } /* get_uint64 */

    /*---------------------------------------------------------------------- */

    size_t integer_generator::data_size() const
    {
        if (_bits > 1)
        {
            return bit_to_byte_size(_bits);
        }
        else
        {
            return 1;
        }

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* integer_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        assert::argument_not_null(buffer, "buffer");
        assert::no_overflow(size >= this->data_size());

        memset(buffer, 0, size);
        memcpy(buffer, &_result, this->data_size());

        return buffer;

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

    uint64_t integer_generator::int_max(size_t bits)
    {
        return (uint64_t)pow(2, bits) - 1;

    } /* int_max */

    /*---------------------------------------------------------------------- */

    size_t integer_generator::bit_to_byte_size(size_t bits)
    {
        return ((bits - 1) / 8) + 1;

    } /* bit_to_byte_size */

    /*---------------------------------------------------------------------- */

    uint8_t integer_generator::chr_value(char chr, size_t base)
    {
        char cur_chr = 0;

        for (size_t pos = 0; pos < base; pos++)
        {
            cur_chr = BASE_CHARS[pos];

            if (chr == tolower(cur_chr) || chr == toupper(cur_chr))
            {
                return (uint8_t)pos;
            }
        }

        return -1;

    } /* chr_value */

    /*---------------------------------------------------------------------- */

    void integer_generator::validate_format(
        const string_t& pattern, size_t base)
    {
        char cur_chr = 0;
        size_t pattern_len = 0;

        pattern_len = pattern.size();

        for (size_t pos = 0; pos < pattern_len; pos++)
        {
            cur_chr = pattern[pos];

            if (cur_chr != RAND_WILDCARD &&
                cur_chr != INCR_WILDCARD &&
                cur_chr != DECR_WILDCARD &&
                chr_value(cur_chr, base) == (uint8_t)-1)
            {
                assert::valid_format(
                    false, "pattern", "contains illegal character");
            }
        }

        assert::valid_format(pattern_len > 0, "pattern", "string is empty");

    } /* validate_format */

    /*---------------------------------------------------------------------- */

    uint64_t integer_generator::digit_value(
        uint64_t value, size_t base, size_t pos)
    {
        if (value >= base && pos > 0)
        {
            return digit_value(value / base, base, pos - 1);
        }
        else
        {
            return value % base;
        }

    } /* digit_value */

    /*---------------------------------------------------------------------- */

    uint64_t integer_generator::replace_wildcards(
        const string_t& pattern, size_t base, size_t value, uint64_t max)
    {
        uint64_t result = 0;
        char cur_chr = 0;
        size_t pattern_len = 0;
        uint64_t base_factor = 0;
        uint64_t digit_value = 0;

        pattern_len = pattern.size();

        for (size_t pos = 0; pos < pattern_len; pos++)
        {
            cur_chr = pattern[pos];

            base_factor = (uint64_t)pow(base, (double)pattern_len - pos - 1);

            if (cur_chr == RAND_WILDCARD ||
                cur_chr == INCR_WILDCARD ||
                cur_chr == DECR_WILDCARD)
            {
                digit_value = value;

                if (result + (digit_value * base_factor) > max)
                {
                    digit_value = integer_generator::digit_value(
                        max, base, pattern_len - pos - 1);
                }
            }
            else
            {
                digit_value = chr_value(cur_chr, base);
            }

            result += digit_value * base_factor;
        }

        return result;

    } /* replace_wildcards */

    /*---------------------------------------------------------------------- */

    uint64_t integer_generator::result_min(uint64_t max) const
    {
        return replace_wildcards(_pattern, _base, 0, max);

    } /* result_min */

    /*---------------------------------------------------------------------- */

    uint64_t integer_generator::result_max(uint64_t max) const
    {
        return replace_wildcards(_pattern, _base, _base - 1, max);

    } /* result_max */

    /*---------------------------------------------------------------------- */

    uint64_t integer_generator::result() const
    {
        uint64_t result = 0;
        char cur_chr = 0;
        uint64_t digit_value = 0;
        uint64_t cur_offset = 0;
        uint64_t next_offset = 0;

        for (size_t pos = _pattern_len - 1; pos != SIZE_NONE; pos--)
        {
            cur_chr = _pattern[pos];

            if (cur_chr == RAND_WILDCARD ||
                cur_chr == INCR_WILDCARD ||
                cur_chr == DECR_WILDCARD)
            {
                if (cur_chr == RAND_WILDCARD)
                {
                    digit_value = rand() % (_base);
                }
                else
                {
                    if ((pos + 1) < _pattern_len &&
                        cur_chr == _pattern[pos + 1])
                    {
                        // If the previous wildcard was also an
                        // incrementation or decrementation wildcard,
                        // use the last base-divided offset instead to
                        // have the current wildcard's incrementation
                        // or decrementation steps to be dependend on
                        // the previous ones.

                        cur_offset = next_offset;
                    }
                    else
                    {
                        cur_offset = _offset;
                    }

                    digit_value = cur_offset % _base;
                    next_offset = cur_offset / _base;

                    if (cur_chr == DECR_WILDCARD)
                    {
                        // If this is a decrementation wildcard,
                        // invert the digit value.

                        digit_value = this->digit_value(
                            _result_max,
                            _base,
                            _pattern_len - pos - 1) - digit_value;
                    }
                }
            }
            else
            {
                digit_value = chr_value(_pattern[pos], _base);
            }

            result +=
                digit_value *
                (uint64_t)pow(_base, (double)_pattern_len - pos - 1);
        }

        return result;

    } /* result */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators */
