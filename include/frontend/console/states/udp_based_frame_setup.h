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

#ifndef UDP_BASED_FRAME_SETUP_H
#define UDP_BASED_FRAME_SETUP_H

#include "../../../../include/frontend/console/states/generator_setup.h"
#include "../../../../include/frontend/console/states/udp_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class udp_based_frame_setup;

    class udp_based_frame_setup :
        public generator_setup
    {
        private:
            udp_frame_setup* _udp_frame_setup;

        public:
            udp_based_frame_setup(
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                console_app_state* parent,
                udp_frame_setup* udp_frame_setup);

            virtual ~udp_based_frame_setup() {};
            virtual bool run() = 0;
            virtual string_t get_generator_name() const = 0;
            virtual data_generator_t* get_generator() const = 0;

        protected:
            virtual void on_select() = 0;
            udp_frame_setup* get_udp_frame_setup() const;

    }; /* udp_based_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* UDP_BASED_FRAME_SETUP_H */
