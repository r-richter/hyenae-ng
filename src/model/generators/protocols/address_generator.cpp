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

#include "../../../../include/assert.h"
#include "../../../../include/model/generators/integer_generator.h"
#include "../../../../include/model/generators/protocols/address_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    const string_t address_generator::RAND_MAC_PATTERN =
        "**:**:**:**:**:**";

    const string_t address_generator::RAND_IP_V4_PATTERN =
        "***.***.***.***";

    const string_t address_generator::RAND_IP_V6_PATTERN =
        "****:****:****:****:****:****:****:****";

    /*---------------------------------------------------------------------- */

    address_generator::address_generator(
        const string_t& pattern,
        size_t base,
        size_t field_count,
        size_t field_bits,
        char field_delimiter,
        data_transformation* field_transformation)
    {
        _address = parse_address(
            pattern,
            base,
            field_count,
            field_bits,
            field_delimiter,
            field_transformation);

        _field_count = _address->generator_count();
        _field_bits = field_bits;
        _base = base;

    } /* address_generator */

    /*---------------------------------------------------------------------- */

    address_generator::~address_generator()
    {
        free_address(_address);

    } /* ~address_generator */

    /*---------------------------------------------------------------------- */

    address_generator* address_generator::create_mac_address(
        const string_t& pattern, data_transformation* field_transformation)
    {
        return new address_generator(
            pattern,
            integer_generator::BASE_HEXADECIMAL,
            6,
            BITS_OCTET,
            ':',
            field_transformation);

    } /* create_mac_address */

    /*---------------------------------------------------------------------- */

    address_generator* address_generator::create_ipv4_address(
        const string_t& pattern, data_transformation* field_transformation)
    {
        return new address_generator(
            pattern,
            integer_generator::BASE_DECIMAL,
            4,
            BITS_OCTET,
            '.',
            field_transformation);

    } /* create_ipv4_address */

    /*---------------------------------------------------------------------- */

    address_generator* address_generator::create_ipv6_address(
        const string_t& pattern, data_transformation* field_transformation)
    {
        return new address_generator(
            pattern,
            integer_generator::BASE_HEXADECIMAL,
            8,
            BITS_HEXTET,
            ':',
            field_transformation);

    } /* create_ipv6_address */

    /*---------------------------------------------------------------------- */

    void address_generator::next(bool data_changed)
    {
        _address->next(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void address_generator::reset(bool data_changed)
    {
        _address->reset(false);

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    void address_generator::to_mac_address(mac_address_t& result) const
    {
        size_t size = sizeof(mac_address_t);

        if (_field_count != 6 ||
            _field_bits != BITS_OCTET ||
            _base != integer_generator::BASE_HEXADECIMAL)
        {
            assert::legal_call(false, "", "address type missmatch");
        }

        to_buffer((byte_t*)&result, size);

    } /* to_mac_address */

    /*---------------------------------------------------------------------- */

    void address_generator::to_ipv4_address(ipv4_address_t& result) const
    {
        size_t size = sizeof(ipv4_address_t);

        if (_field_count != 4 ||
            _field_bits != BITS_OCTET ||
            _base != integer_generator::BASE_DECIMAL)
        {
            assert::legal_call(false, "", "address type missmatch");
        }

        to_buffer((byte_t*)&result, size);

    } /* to_ipv4_address */

    /*---------------------------------------------------------------------- */

    void address_generator::to_ipv6_address(ipv6_address_t& result) const
    {
        size_t size = sizeof(ipv6_address_t);

        if (_field_count != 8 ||
            _field_bits != BITS_HEXTET ||
            _base != integer_generator::BASE_HEXADECIMAL)
        {
            assert::legal_call(false, "", "address type missmatch");
        }

        to_buffer((byte_t*)&result, size);

    } /* to_ipv6_address */

    /*---------------------------------------------------------------------- */

    size_t address_generator::data_size() const
    {
        return _address->size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* address_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _address->to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

    generator_group* address_generator::parse_address(
        const string_t& pattern,
        size_t base,
        size_t field_count,
        size_t field_bits,
        char field_delimiter,
        data_transformation* field_transformation)
    {
        generator_group* address = NULL;
        string_t pattern_str = pattern;
        string_t field_str;
        size_t pos = 0;
        integer_generator* field_generator = NULL;

        try
        {
            address = new generator_group();

            do
            {
                pos = pattern_str.find(field_delimiter);
                field_str = pattern_str.substr(0, pos);
                
                field_generator =
                    new integer_generator(field_str.c_str(), base, field_bits);

                if (field_generator == NULL)
                {
                    break;
                }

                if (field_transformation != NULL)
                {
                    field_generator->add_transformation(field_transformation);
                }

                address->add_generator(field_generator);

                pattern_str.erase(0, pos + 1);

            } while (pos != string_t::npos);

            if (address->generator_count() != field_count)
            {
                assert::valid_format(
                    false, "pattern", "invalid delimiter count");
            }
        }
        catch (const runtime_error_t&)
        {
            free_address(address);

            throw;
        }

        return address;

    } /* parse_address */

    /*---------------------------------------------------------------------- */

    void address_generator::free_address(generator_group* address)
    {
        size_t size = address->generator_count();

        for (size_t i = 0; i < size; i++)
        {
            delete address->generator_at(i);
        }

        delete address;

    } /* free_address */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
