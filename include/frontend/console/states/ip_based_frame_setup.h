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

#ifndef IP_BASED_FRAME_SETUP_H
#define IP_BASED_FRAME_SETUP_H

#include "../../../../include/frontend/console/states/generator_setup.h"
#include "../../../../include/frontend/console/states/ip_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class ip_based_frame_setup;

    class ip_based_frame_setup :
        public generator_setup
    {
        private:
            ip_frame_setup* _ip_frame_setup;

        public:
            ip_based_frame_setup(
                console_app_state_context* context,
                app_config* config,
                console_io* console_io,
                console_app_state* parent,
                ip_frame_setup* ip_frame_setup);

            virtual ~ip_based_frame_setup() {};
            virtual bool run() = 0;
            virtual string_t get_generator_name() const = 0;
            virtual data_generator_t* get_generator() const = 0;

        protected:
            virtual void on_select() = 0;
            ip_frame_setup* get_ip_frame_setup() const;

    }; /* ip_based_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* IP_BASED_FRAME_SETUP_H */
