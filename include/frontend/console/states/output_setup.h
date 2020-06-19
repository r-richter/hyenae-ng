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

#ifndef OUTPUT_SETUP_H
#define OUTPUT_SETUP_H

#include "../../../../include/model/data_output.h"
#include "../../../../include/model/outputs/network_output.h"
#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/console_app_state.h"
#include "../../../../include/frontend/console/states/network_device_selector.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class main_menu;

    class output_setup :
        public console_app_state
    {
        using data_output_t = hyenae::model::data_output;

        using device_t = hyenae::model::outputs::network_output::device;

        private:
            static const char* FILE_OUTPUT_PATH;

            network_device_selector* _network_device_selector = NULL;
            console_menu* _menu = NULL;
            unordered_map_t<console_menu::item*, data_output_t*> _menu_items;
            console_menu::item* _file_output_item = NULL;
            console_menu::item* _network_output_item = NULL;
            console_menu::item* _selected_item = NULL;
            data_output_t* _output = NULL;
            string_t _file_path;
            string_t _network_error;

        public:
            output_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent);
            
            ~output_setup();
            bool run();
            data_output_t* get_output() const;

        private:
            void update_menu_items();
            void update_network_output();

            console_menu::item* add_output(
                string_t caption, data_output_t* output);

            data_output_t* select_file_output(bool setup);

    }; /* main_menu */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* OUTPUT_SETUP_H */
