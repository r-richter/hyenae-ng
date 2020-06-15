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

#ifndef ETHERNET_BASED_FRAME_SETUP_H
#define ETHERNET_BASED_FRAME_SETUP_H

#include "../../../../include/frontend/console/states/generator_setup.h"
#include "../../../../include/frontend/console/states/ethernet_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class ethernet_frame_setup;

    class ethernet_based_frame_setup :
        public generator_setup
    {
        private:
            ethernet_frame_setup* _ethernet_frame_setup;

        public:
            ethernet_based_frame_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent,
                ethernet_frame_setup* ethernet_frame_setup);

            virtual ~ethernet_based_frame_setup() {};
            virtual bool run() = 0;
            virtual uint8_t get_protocol() const = 0;
            virtual void set_protocol(uint8_t protocol) = 0;
            virtual string_t get_generator_name() const = 0;
            virtual data_generator_t* get_generator() const = 0;
            virtual data_generator_t* get_pseudo_header() const = 0;

        protected:
            virtual void on_select() = 0;
            ethernet_frame_setup* get_ethernet_frame_setup() const;

    }; /* ethernet_based_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* ETHERNET_BASED_FRAME_SETUP_H */
