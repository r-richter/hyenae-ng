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

#ifndef ARP_FRAME_SETUP_H
#define ARP_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/generator_setup.h"
#include "../../../../include/frontend/console/states/ethernet_frame_setup.h"
#include "../../../../include/model/generators/protocols/ethernet_frame_generator.h"
#include "../../../../include/model/generators/protocols/arp_frame_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class arp_frame_setup :
        public generator_setup
    {
        using address_generator_t =
            model::generators::protocols::address_generator;

        using ethernet_frame_generator_t =
            model::generators::protocols::ethernet_frame_generator;

        using arp_frame_generator_t =
            model::generators::protocols::arp_frame_generator;

        private:
            ethernet_frame_setup* _ethernet_frame_setup;
            console_menu* _menu = NULL;
            console_menu::item* _operation_item = NULL;
            console_menu::item* _sender_hw_addr_pattern_item = NULL;
            console_menu::item* _sender_proto_addr_pattern_item = NULL;
            console_menu::item* _target_hw_addr_pattern_item = NULL;
            console_menu::item* _target_proto_addr_pattern_item = NULL;
            data_generator_t* _generator = NULL;
            uint16_t _operation;
            string_t _sender_hw_addr_pattern;
            string_t _sender_proto_addr_pattern;
            string_t _target_hw_addr_pattern;
            string_t _target_proto_addr_pattern;

        public:
            arp_frame_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent,
                ethernet_frame_setup* ethernet_frame_setup);

            ~arp_frame_setup();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select();

        private:
            void update_menu_items();
            void prompt_operation();
            void prompt_sender_hw_addr_pattern();
            void prompt_sender_proto_addr_pattern();
            void prompt_target_hw_addr_pattern();
            void prompt_target_proto_addr_pattern();

            void update_generator(
                string_t sender_hw_addr_pattern,
                string_t sender_proto_addr_pattern,
                string_t target_hw_addr_pattern,
                string_t target_proto_addr_pattern);

    }; /* arp_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* ARP_FRAME_SETUP_H */
