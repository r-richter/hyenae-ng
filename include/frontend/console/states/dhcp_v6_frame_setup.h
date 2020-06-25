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

#ifndef DHCP_V6_FRAME_SETUP_H
#define DHCP_V6_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/udp_based_frame_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/model/generators/protocols/dhcp_v6_frame_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class dhcp_v6_frame_setup :
        public udp_based_frame_setup
    {
        using dhcp_v6_frame_generator_t =
            model::generators::protocols::dhcp_v6_frame_generator;

        private:
            console_menu* _menu = NULL;
            console_menu::item* _msg_type_item = NULL;
            console_menu::item* _transaction_id_pattern_item = NULL;
            console_menu::item* _payload_item = NULL;
            data_generator_t* _generator = NULL;
            uint8_t _msg_type;
            string_t _transaction_id_pattern;
            generator_selector* _payload = NULL;

        public:
            dhcp_v6_frame_setup(
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                console_app_state* parent,
                udp_frame_setup* udp_frame_setup);

            ~dhcp_v6_frame_setup();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select();

        private:
            void update_menu_items();
            void prompt_msg_type_item();
            void prompt_transaction_id_pattern_item();
            void update_generator(string_t transaction_id_pattern);

    }; /* dhcp_v6_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* DHCP_V6_FRAME_SETUP_H */
