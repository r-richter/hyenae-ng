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

#ifndef DISPATCHER_SETUP_H
#define DISPATCHER_SETUP_H

#include "../../../../include/model/data_dispatcher.h"
#include "../../../../include/model/fixed_duration_generator.h"
#include "../../../../include/model/random_duration_generator.h"
#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/console_app_state.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class main_menu;

    class dispatcher_setup :
        public console_app_state
    {
        using limits_t = hyenae::model::data_dispatcher::limits;
        using delay_t = hyenae::model::duration_generator;
        using fixed_delay_t = hyenae::model::fixed_duration_generator;
        using random_delay_t = hyenae::model::random_duration_generator;

        private:
            enum class delay_type
            {
                NONE = 0,
                FIXED = 1,
                RANDOM = 2

            }; /* delay_type */

            console_menu* _menu = NULL;
            console_menu::item* _byte_limit_item = NULL;
            console_menu::item* _packet_limit_item = NULL;
            console_menu::item* _duration_limit_item = NULL;
            console_menu::item* _send_delay_item = NULL;
            console_menu::item* _back_item = NULL;
            limits_t* _limits;
            delay_t* _delay;
            delay_type _delay_type;

        public:
            dispatcher_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent);

            ~dispatcher_setup();
            bool run();
            limits_t* get_limits();
            delay_t* get_delay();

        private:
            void update_menu_items();
            void prompt_byte_limit();
            void prompt_packet_limit();
            void prompt_duration_limit();
            void prompt_send_delay();
            void prompt_fixed_send_delay();
            void prompt_random_send_delay();

    }; /* main_menu */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* DISPATCHER_SETUP_H */
