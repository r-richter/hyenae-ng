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

#ifndef GENERATOR_SELECTOR_H
#define GENERATOR_SELECTOR_H

#include "../../../../include/model/data_generator.h"
#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/generator_setup.h"


namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class main_menu;
    class ip_v4_frame_setup;
    class ip_v6_frame_setup;
    class icmp_v4_frame_setup;
    class icmp_v6_frame_setup;
    class ethernet_frame_setup;
    class udp_over_ip_v4_frame_setup;
    class udp_over_ip_v6_frame_setup;

    class generator_selector :
        public generator_setup
    {
        private:
            /* Generator Flags */
            static const size_t GFLAG_ETHERNET_FRAME = 0x1 << 0;
            static const size_t GFLAG_ARP_FRAME = 0x1 << 1;
            static const size_t GFLAG_IP_V4_FRAME = 0x1 << 2;
            static const size_t GFLAG_IP_V6_FRAME = 0x1 << 3;
            static const size_t GFLAG_ICMP_V4_OVER_IP_V4_FRAME = 0x1 << 4;
            static const size_t GFLAG_ICMP_V4_OVER_IP_V6_FRAME = 0x1 << 5;
            static const size_t GFLAG_ICMP_V6_FRAME = 0x1 << 6;
            static const size_t GFLAG_ICMP_V4_ECHO_PAYLOAD = 0x1 << 7;
            static const size_t GFLAG_ICMP_V6_ECHO_PAYLOAD = 0x1 << 8;
            static const size_t GFLAG_TCP_OVER_IP_V4_FRAME = 0x1 << 9;
            static const size_t GFLAG_TCP_OVER_IP_V6_FRAME = 0x1 << 10;
            static const size_t GFLAG_UDP_OVER_IP_V4_FRAME = 0x1 << 11;
            static const size_t GFLAG_UDP_OVER_IP_V6_FRAME = 0x1 << 12;
            static const size_t GFLAG_BOOTP = 0x1 << 13;
            static const size_t GFLAG_DHCP_V6 = 0x1 << 14;
            static const size_t GFLAG_TEXT_BUFFER = 0x1 << 15;

            bool _init = false;
            string_t _title;
            size_t _generator_flags;
            console_menu* _menu = NULL;

            unordered_map_t<
                console_menu::item*,
                generator_setup*> _menu_items;

            console_menu::item* _none_item = NULL;
            console_menu::item* _selected_item = NULL;
            generator_setup* _selected_setup = NULL;

        public:
            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                console_app_state* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                generator_setup* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                ethernet_frame_setup* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                ip_v4_frame_setup* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                ip_v6_frame_setup* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                icmp_v4_frame_setup* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                icmp_v6_frame_setup* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                udp_over_ip_v4_frame_setup* parent);

            generator_selector(
                string_t title,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                udp_over_ip_v6_frame_setup* parent);

            ~generator_selector();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select() {};

        private:
            void inizialize();
            void update_menu_items();
            void add_generator(generator_setup* setup_state);

    }; /* generator_selector */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* GENERATOR_SELECTOR_H */
