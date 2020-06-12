/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
 *   Homepage : http://sourceforge.net/projects/hyenae-ng/
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

#ifndef ETHERNET_FRAME_SETUP_H
#define ETHERNET_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/generator_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/model/generators/protocols/ethernet_frame_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class generator_selector;

    class ethernet_frame_setup :
        public generator_setup
    {
        using address_generator_t =
            model::generators::protocols::address_generator;

        using ethernet_frame_generator_t =
            model::generators::protocols::ethernet_frame_generator;

        private:
            console_menu* _menu = NULL;
            console_menu::item* _add_preamble_sfd_item = NULL;
            console_menu::item* _src_mac_pattern_item = NULL;
            console_menu::item* _dst_mac_pattern_item = NULL;
            console_menu::item* _type_item = NULL;
            console_menu::item* _add_fcs_item = NULL;
            console_menu::item* _payload_item = NULL;
            console_menu::item* _back_item = NULL;
            data_generator_t* _generator = NULL;
            bool _add_preamble_sfd;
            string_t _src_mac_pattern;
            string_t _dst_mac_pattern;
            uint16_t _type;
            bool _add_fcs;
            generator_selector* _payload = NULL;

        public:
            ethernet_frame_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent);

            ~ethernet_frame_setup();
            bool run();
            uint16_t get_type() const;
            void set_type(uint16_t type);
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select() {};

        private:
            void update_menu_items();
            void prompt_add_preamble_sfd();
            void prompt_src_mac_pattern();
            void prompt_dst_mac_pattern();
            void prompt_add_fcs();
            void prompt_type();
            
            void update_generator(
                string_t src_mac_pattern, string_t dst_mac_pattern);

    }; /* ethernet_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* ETHERNET_FRAME_SETUP_H */
