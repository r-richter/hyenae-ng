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

#ifndef ICMP_ECHO_PAYLOAD_SETUP_H
#define ICMP_ECHO_PAYLOAD_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/icmp_frame_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/model/generators/protocols/icmp_echo_payload_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class icmp_echo_payload_setup :
        public generator_setup
    {
        using icmp_echo_payload_generator_t =
            model::generators::protocols::icmp_echo_payload_generator;

        private:
            uint8_t _type;
            uint8_t _code;
            icmp_frame_setup* _icmp_frame_setup;
            console_menu* _menu = NULL;
            console_menu::item* _id_pattern_item = NULL;
            console_menu::item* _seq_num_pattern_item = NULL;
            data_generator_t* _generator = NULL;
            string_t _id_pattern;
            string_t _seq_num_pattern;

        public:
            icmp_echo_payload_setup(
                uint8_t type,
                uint8_t code,
                console_app_state_context* context,
                app_config* config,
                console_io* console_io,
                console_app_state* parent,
                icmp_frame_setup* icmp_frame_setup);

            ~icmp_echo_payload_setup();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select();

        private:
            void update_menu_items();
            void prompt_id_pattern();
            void prompt_seq_num_pattern();
            
            void update_generator(
                string_t id_pattern,
                string_t seq_num_pattern);

    }; /* icmp_echo_payload_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* ICMP_ECHO_PAYLOAD_SETUP_H */
