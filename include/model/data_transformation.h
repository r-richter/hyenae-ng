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

#ifndef DATA_TRANSFORMATION_H
#define DATA_TRANSFORMATION_H

#include "../common.h"

namespace hyenae::model
{
    /*---------------------------------------------------------------------- */

    class data_transformation
    {
        public:
            virtual ~data_transformation() {};
            virtual size_t result_size(size_t data_size) const = 0;
            virtual byte_t* transform(byte_t* data, size_t size) const = 0;

    }; /* data_transformation */

    /*---------------------------------------------------------------------- */

} /* hyenae::model */

#endif /* DATA_TRANSFORMATION_H */
