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
#include "../../../../include/frontend/console/states/icmp_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    icmp_frame_setup::icmp_frame_setup(
        console_app_state_context* context,
        console_app_config* config,
        console_io* console_io,
        console_app_state* parent,
        ip_frame_setup* ip_frame_setup) :
            ip_based_frame_setup(
                context,
                config,
                console_io,
                parent,
                ip_frame_setup)
    {
        assert::argument_not_null(
            ip_frame_setup, "ip_frame_setup");

        _ip_frame_setup = ip_frame_setup;

    } /* icmp_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
