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

#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#include "data_generator.h"

namespace hyenae::model
{
    /*---------------------------------------------------------------------- */

    class generator_group :
        public data_generator, generator_listener
    {
        private:
            vector_t<data_generator*> _generators;

        public:
            size_t generator_count() const;
            data_generator* generator_at(const size_t pos) const;
            void add_generator(data_generator* generator);
            void remove_generator_at(const size_t pos);
            void next(bool data_changed = true);
            void reset(bool data_changed = true);

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

        protected:
            void on_data_changed();

    }; /* generator_group */

    /*---------------------------------------------------------------------- */

} /* hyenae::model */

#endif /* GENERATOR_GROUP_H */
