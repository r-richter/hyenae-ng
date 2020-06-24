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

#ifndef TCP_FRAME_SETUP_H
#define TCP_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/tcp_flags_setup.h"
#include "../../../../include/frontend/console/states/ip_based_frame_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/model/generators/protocols/tcp_frame_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class tcp_flags_setup;

    class tcp_frame_setup :
        public ip_based_frame_setup
    {
        friend class tcp_flags_setup;

        using tcp_frame_generator_t =
            model::generators::protocols::tcp_frame_generator;

        private:
            uint8_t _protocol;
            tcp_flags_setup* _flags_setup = NULL;
            console_menu* _menu = NULL;
            console_menu::item* _src_port_pattern_item = NULL;
            console_menu::item* _dst_port_pattern_item = NULL;
            console_menu::item* _seq_num_pattern_item = NULL;
            console_menu::item* _ack_num_pattern_item = NULL;
            console_menu::item* _flags_item = NULL;
            console_menu::item* _win_size_pattern_item = NULL;
            console_menu::item* _urg_pointer_pattern_item = NULL;
            console_menu::item* _payload_item = NULL;
            data_generator_t* _generator = NULL;
            string_t _src_port_pattern;
            string_t _dst_port_pattern;
            string_t _seq_num_pattern;
            string_t _ack_num_pattern;
            string_t _win_size_pattern;
            string_t _urg_pointer_pattern;
            generator_selector* _payload = NULL;

        public:
            tcp_frame_setup(
                uint8_t protocol,
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                console_app_state* parent,
                ip_frame_setup* ip_frame_setup);

            ~tcp_frame_setup();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select();

        private:
            void update_menu_items();
            void prompt_src_port_pattern();
            void prompt_dst_port_pattern();
            void prompt_seq_num_pattern();
            void prompt_ack_num_pattern();
            void prompt_win_size_pattern();
            void prompt_urg_pointer_pattern();
            
            void update_generator(
                string_t src_port_pattern,
                string_t dst_port_pattern,
                string_t seq_num_pattern,
                string_t ack_num_pattern,
                string_t win_size_pattern,
                string_t urg_pointer_pattern);

    }; /* tcp_frame_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* TCP_FRAME_SETUP_H */
