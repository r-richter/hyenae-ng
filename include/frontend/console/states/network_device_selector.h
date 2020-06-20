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

#ifndef NETWORK_DEVICE_SELECTOR_H
#define NETWORK_DEVICE_SELECTOR_H

#include "../../../../include/model/outputs/network_output.h"
#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/console_app_state.h"
#include "../../../../include/frontend/console/states/output_setup.h"
#include "../../../../include/frontend/console/states/startable_state.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class output_setup;

    class network_device_selector :
        public startable_state,
        public console_app_state
    {
        using device_t = hyenae::model::outputs::network_output::device;

        private:
            console_menu* _menu = NULL;
            unordered_map_t<console_menu::item*, device_t*> _menu_items;
            console_menu::item* _selected_item = NULL;
            device_t* _device = NULL;

        public:
            network_device_selector(
                console_app_state_context* context,
                console_io* console_io,
                output_setup* parent);
            
            ~network_device_selector();
            bool run();
            device_t* get_device() const;

        private:
            console_menu::item* add_device(device_t* device);

    }; /* main_menu */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* NETWORK_DEVICE_SELECTOR_H */
