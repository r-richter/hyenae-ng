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
#include "../../../../include/model/generators/protocols/bootp_option_generator.h"

namespace hyenae::model::generators::protocols
{
	/*---------------------------------------------------------------------- */

	bootp_option_generator::bootp_option_generator(
		uint8_t code,
		data_generator* value)
    {
        assert::argument_not_null(value, "value");

		// Code
		_code = fixed_data_generator::allocate_uint8();
		_code->set_uint8(code);
		_packet.add_generator(_code);

		// Length
		_length = fixed_data_generator::allocate_uint8();
		_packet.add_generator(_length);

		// Value
        _value = value;
		_packet.add_generator(_value);

        // vendor
        _packet.add_generator(&_vendor);

        // Update fields
        update_option_length();

    } /* bootp_option_generator */

	/*---------------------------------------------------------------------- */

    bootp_option_generator::~bootp_option_generator()
    {
		safe_delete(_code);
		safe_delete(_length);

    } /* ~bootp_option_generator */

    /*---------------------------------------------------------------------- */

    void bootp_option_generator::next(bool data_changed)
    {
		_value->next(false);

        update_option_length();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void bootp_option_generator::reset(bool data_changed)
    {
		_value->reset(false);

        update_option_length();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* bootp_option_generator::get_vendor()
    {
        return &_vendor;

    } /* get_vendor */

    /*---------------------------------------------------------------------- */

    size_t bootp_option_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* bootp_option_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

     void bootp_option_generator::update_option_length()
     {
         _length->set_uint8(value->size());

     } /* update_option_length */

     /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
