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

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../../../../include/file_io.h"
#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/console_app_state.h"
#include "../../../../include/frontend/console/console_app_config.h"
#include "../../../../include/frontend/console/states/output_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/frontend/console/states/dispatcher_setup.h"
#include "../../../../include/frontend/console/states/start_dispatcher.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class main_menu :
        public console_app_state
    {
        using limits_t = model::data_dispatcher::limits;
        using delay_t = model::duration_generator;

        private:
            console_menu* _menu = NULL;
            console_menu::item* _output_setup_item = NULL;
            console_menu::item* _generator_selector_item = NULL;
            console_menu::item* _dispatcher_setup_item = NULL;
            states::output_setup* _output_setup = NULL;
            states::generator_selector* _generator_selector = NULL;
            states::dispatcher_setup* _dispatcher_setup = NULL;
            states::start_dispatcher* _start_dispatcher = NULL;

        public:
            main_menu(
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                file_io::provider file_io_provider);

            ~main_menu();
            bool run();

    }; /* main_menu */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* MAIN_MENU_H */
