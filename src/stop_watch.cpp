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

#include "../include/stop_watch.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    stop_watch::stop_watch()
    {
        reset();

    } /* stop_watch */

    /*---------------------------------------------------------------------- */

    duration_t stop_watch::get_time_passed() const
    {
        duration_t now = duration_t{ 0 };

        if (_started_at != duration_t{ 0 })
        {
            if (_stopped_at != duration_t{ 0 })
            {
                now = _stopped_at;
            }
            else
            {
                now = clock_t::now().time_since_epoch();
            }

            return now - _started_at;
        }
        
        return duration_t{ 0 };

    } /* get_time_passed */

    /*---------------------------------------------------------------------- */

    void stop_watch::start()
    {
        _started_at = clock_t::now().time_since_epoch();
        _stopped_at = duration_t{ 0 };

    } /* start */

    /*---------------------------------------------------------------------- */

    void stop_watch::stop()
    {
        if (_started_at != duration_t{ 0 })
        {
            _stopped_at = clock_t::now().time_since_epoch();
        }

    } /* stop */

    /*---------------------------------------------------------------------- */

    void stop_watch::reset()
    {
        _started_at = duration_t{ 0 };
        _stopped_at = duration_t{ 0 };

    } /* reset */

    /*---------------------------------------------------------------------- */

} /* hyenae */
