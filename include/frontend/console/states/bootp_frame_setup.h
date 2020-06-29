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

#ifndef BOOTP_FRAME_SETUP_H
#define BOOTP_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/udp_based_frame_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/model/generators/protocols/bootp_frame_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class bootp_frame_setup :
        public udp_based_frame_setup
    {
        using address_generator_t =
            model::generators::protocols::address_generator;

        using bootp_frame_generator_t =
            model::generators::protocols::bootp_frame_generator;

        private:
            console_menu* _menu = NULL;
            console_menu::item* _opcode_item = NULL;
            console_menu::item* _hops_item = NULL;
            console_menu::item* _transaction_id_item = NULL;
            console_menu::item* _seconds_item = NULL;
            console_menu::item* _broadcast_flag_item = NULL;
            console_menu::item* _client_ip_addr_item = NULL;
            console_menu::item* _your_ip_addr_item = NULL;
            console_menu::item* _server_ip_addr_item = NULL;
            console_menu::item* _gateway_ip_addr_item = NULL;
            console_menu::item* _client_mac_addr_item = NULL;
            console_menu::item* _server_name_item = NULL;
            console_menu::item* _file_item = NULL;
            console_menu::item* _vendor_item = NULL;
            data_generator_t* _generator = NULL;
            uint8_t _opcode;
            uint8_t _hops;
            string_t _transaction_id_pattern;
            size_t _transaction_id_pattern_base;
            string_t _seconds_pattern;
            size_t _seconds_pattern_base;
            bool _broadcast_flag;
            string_t _client_ip_pattern;
            string_t _your_ip_pattern;
            string_t _server_ip_pattern;
            string_t _gateway_ip_pattern;
            string_t _client_mac_pattern;
            string_t _server_name;
            string_t _file_name;
            generator_selector* _vendor = NULL;

        public:
            bootp_frame_setup(
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                console_app_state* parent,
                udp_frame_setup* udp_frame_setup);

            ~bootp_frame_setup();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select();

        private:
            void update_menu_items();
            void prompt_opcode();
            void prompt_hops();
            void prompt_transaction_id();
            void prompt_seconds();
            void prompt_broadcast_flag();
            void prompt_client_ip_addr();
            void prompt_your_ip_addr();
            void prompt_server_ip_addr();
            void prompt_gateway_ip_addr();
            void prompt_client_mac_addr();
            void prompt_server_name();
            void prompt_file_name();
            void update_generator(
                string_t transaction_id_pattern,
                string_t seconds_pattern,
                string_t client_ip_pattern,
                string_t your_ip_pattern,
                string_t server_ip_pattern,
                string_t gateway_ip_pattern,
                string_t client_mac_pattern);

    }; /* bootp_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* BOOTP_FRAME_SETUP_H */
