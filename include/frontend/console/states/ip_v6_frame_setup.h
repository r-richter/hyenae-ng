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

#ifndef IP_V6_FRAME_SETUP_H
#define IP_V6_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/ethernet_based_frame_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/frontend/console/states/ethernet_frame_setup.h"
#include "../../../../include/model/generators/protocols/ethernet_frame_generator.h"
#include "../../../../include/model/generators/protocols/ip_v6_frame_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class generator_selector;

    class ip_v6_frame_setup :
        public ethernet_based_frame_setup
    {
        using address_generator_t =
            model::generators::protocols::address_generator;

        using ethernet_frame_generator_t =
            model::generators::protocols::ethernet_frame_generator;

        using ip_v6_frame_generator_t =
            model::generators::protocols::ip_v6_frame_generator;

        private:
            console_menu* _menu = NULL;
            console_menu::item* _traffic_class_item = NULL;
            console_menu::item* _flow_label_pattern_item = NULL;
            console_menu::item* _next_header_item = NULL;
            console_menu::item* _hop_limit_item = NULL;
            console_menu::item* _src_ip_pattern_item = NULL;
            console_menu::item* _dst_ip_pattern_item = NULL;
            console_menu::item* _payload_item = NULL;
            console_menu::item* _back_item = NULL;
            data_generator_t* _generator = NULL;
            uint8_t _traffic_class;
            string_t _flow_label_pattern;
            uint8_t _next_header;
            uint8_t _hop_limit;
            string_t _src_ip_pattern;
            string_t _dst_ip_pattern;
            generator_selector* _payload = NULL;

        public:
            ip_v6_frame_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent,
                ethernet_frame_setup* ethernet_frame_setup);

            ~ip_v6_frame_setup();
            bool run();
            uint8_t get_protocol() const;
            void set_protocol(uint8_t protocol);
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            data_generator_t* get_pseudo_header() const;
            void update_generator();

        protected:
            void on_select();

        private:
            void update_menu_items();
            void prompt_traffic_class();
            void prompt_flow_label_pattern();
            void prompt_next_header();
            void prompt_hop_limit();
            void prompt_src_ip_pattern();
            void prompt_dst_ip_pattern();
            
            void update_generator(
                string_t flow_label_pattern,
                string_t src_ip_pattern,
                string_t dst_ip_pattern);

    }; /* ip_v6_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* IP_V6_FRAME_SETUP_H */
