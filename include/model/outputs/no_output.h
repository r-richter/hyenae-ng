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

#ifndef NO_OUTPUT_H
#define NO_OUTPUT_H

#include "../../common.h"
#include "../../model/data_output.h"

namespace hyenae::model::outputs
{
    /*---------------------------------------------------------------------- */

    class no_output :
        public data_output
    {
        public:
            void open() {}
            void close() noexcept {}
            void send(byte_t* data, size_t size) {};

    }; /* no_output */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::outputs */

#endif /* NO_OUTPUT_H */
