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

#ifndef ICMP_V4_FRAME_SETUP_H
#define ICMP_V4_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/icmp_frame_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/model/generators/protocols/icmp_v4_frame_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class icmp_v4_frame_setup :
        public icmp_frame_setup
    {
        using icmp_v4_frame_generator_t =
            model::generators::protocols::icmp_v4_frame_generator;

        private:
            uint8_t _protocol;
            console_menu* _menu = NULL;
            console_menu::item* _type_item = NULL;
            console_menu::item* _code_item = NULL;
            console_menu::item* _payload_item = NULL;
            data_generator_t* _generator = NULL;
            uint8_t _type;
            uint8_t _code;
            generator_selector* _payload = NULL;

        public:
            icmp_v4_frame_setup(
                uint8_t protocol,
                console_app_state_context* context,
                app_config* config,
                console_io* console_io,
                console_app_state* parent,
                ip_frame_setup* ip_frame_setup);

            ~icmp_v4_frame_setup();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            uint8_t get_type() const;
            void set_type(uint8_t type);
            uint8_t get_code() const;
            void set_code(uint8_t code);
            void update_generator();

        protected:
            void on_select();

        private:
            void update_menu_items();
            void prompt_type();
            void prompt_code();

    }; /* icmp_v4_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* ICMP_V4_FRAME_SETUP_H */
