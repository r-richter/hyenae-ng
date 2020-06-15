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
#include "../../include/model/random_duration_generator.h"

#include <ctime>
#include <cstdlib>

namespace hyenae::model
{
    /*---------------------------------------------------------------------- */

    random_duration_generator::random_duration_generator(
        duration_t min_duration, duration_t max_duration)
    {
        assert::in_range(
            min_duration <= max_duration, "min_duration", "bigger than max");

        _min_duration = min_duration;
        _max_duration = max_duration;

        srand((unsigned int)time(NULL));

    } /* random_duration_generator */

    /*---------------------------------------------------------------------- */

    duration_t random_duration_generator::get_min_duration()
    {
        return _min_duration;

    } /* get_min_duration */

    /*---------------------------------------------------------------------- */

    duration_t random_duration_generator::get_max_duration()
    {
        return _max_duration;

    } /* get_max_duration */

    /*---------------------------------------------------------------------- */

    duration_t random_duration_generator::next()
    {
        return duration_t
        {
            rand() %
            (_max_duration.count() - _min_duration.count() + 1) +
            _min_duration.count()
        };

    } /* next */

    /*---------------------------------------------------------------------- */

} /* hyenae::model */
