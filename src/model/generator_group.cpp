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

#include "../../include/assert.h"
#include "../../include/model/generator_group.h"

#include <cstdlib>

namespace hyenae::model
{
    /*---------------------------------------------------------------------- */

    size_t generator_group::generator_count() const
    {
        return _generators.size();

    } /* generator_count */

    /*---------------------------------------------------------------------- */

    data_generator* generator_group::generator_at(const size_t pos) const
    {
        return _generators.at(pos);

    } /* generator_at */

    /*---------------------------------------------------------------------- */

    void generator_group::add_generator(data_generator* generator)
    {
        _generators.push_back(generator);
        generator->add_listener(this);

    } /* add_generator */

    /*---------------------------------------------------------------------- */

    void generator_group::remove_generator_at(const size_t pos)
    {
        assert::in_range(pos < _generators.size(), "pos");

        _generators[pos]->remove_listener(this);
        _generators.erase(_generators.begin() + pos);

    } /* remove_generator_at */

    /*---------------------------------------------------------------------- */

    void generator_group::next(bool data_changed)
    {
        for (auto generator : _generators)
        {
            generator->next(false);
        }

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void generator_group::reset(bool data_changed)
    {
        for (auto generator : _generators)
        {
            generator->reset(false);
        }

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    size_t generator_group::data_size() const
    {
        size_t size = 0;

        for (auto generator : _generators)
        {
            size += generator->size();
        }

        return size;

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* generator_group::data_to_buffer(byte_t* buffer, size_t size) const
    {
        size_t pos = 0;
        size_t data_size = 0;

        assert::argument_not_null(buffer, "buffer");
        assert::no_overflow(size >= this->data_size());

        for (auto generator : _generators)
        {
            data_size = generator->size();

            generator->to_buffer(buffer + pos, data_size);
            pos += data_size;
        }

        return buffer;

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

    void generator_group::on_data_changed()
    {
        data_changed();

    } /* on_data_changed */

    /*---------------------------------------------------------------------- */

} /* hyenae::model */
