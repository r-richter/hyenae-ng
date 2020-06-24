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

#ifndef ICMP_FRAME_SETUP_H
#define ICMP_FRAME_SETUP_H

#include "../../../../include/frontend/console/states/generator_setup.h"
#include "../../../../include/frontend/console/states/ip_based_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class ip_frame_setup;

    class icmp_frame_setup :
        public ip_based_frame_setup
    {
        private:
            ip_frame_setup* _ip_frame_setup;

        public:
            icmp_frame_setup(
                console_app_state_context* context,
                app_config* config,
                console_io* console_io,
                console_app_state* parent,
                ip_frame_setup* ip_frame_setup);

            virtual ~icmp_frame_setup() {};
            virtual bool run() = 0;
            virtual string_t get_generator_name() const = 0;
            virtual data_generator_t* get_generator() const = 0;
            virtual uint8_t get_type() const = 0;
            virtual void set_type(uint8_t type) = 0;
            virtual uint8_t get_code() const = 0;
            virtual void set_code(uint8_t code) = 0;

        protected:
            virtual void on_select() = 0;

    }; /* icmp_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* ICMP_FRAME_SETUP_H */
