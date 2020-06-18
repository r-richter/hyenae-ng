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

#ifndef TCP_FLAGS_SETUP_H
#define TCP_FLAGS_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/console_app_state.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class tcp_flags_setup :
        public console_app_state
    {
        private:
            console_menu* _menu = NULL;
            console_menu::item* _cwr_flag_item = NULL;
            console_menu::item* _ece_flag_item = NULL;
            console_menu::item* _urg_flag_item = NULL;
            console_menu::item* _ack_flag_item = NULL;
            console_menu::item* _psh_flag_item = NULL;
            console_menu::item* _rst_flag_item = NULL;
            console_menu::item* _syn_flag_item = NULL;
            console_menu::item* _fin_flag_item = NULL;
            console_menu::item* _back_item = NULL;
            bool _cwr_flag;
            bool _ece_flag;
            bool _urg_flag;
            bool _ack_flag;
            bool _psh_flag;
            bool _rst_flag;
            bool _syn_flag;
            bool _fin_flag;

        public:
            tcp_flags_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent);

            ~tcp_flags_setup();
            bool run();
            bool get_cwr_flag() const;
            bool get_ece_flag() const;
            bool get_urg_flag() const;
            bool get_ack_flag() const;
            bool get_psh_flag() const;
            bool get_rst_flag() const;
            bool get_syn_flag() const;
            bool get_fin_flag() const;
            string_t get_flags_info() const;

        private:
            void update_menu_items();
            void prompt_cwr_flag();
            void prompt_ece_flag();
            void prompt_urg_flag();
            void prompt_ack_flag();
            void prompt_psh_flag();
            void prompt_rst_flag();
            void prompt_syn_flag();
            void prompt_fin_flag();

    }; /* tcp_flags_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* TCP_FLAGS_SETUP_H */
