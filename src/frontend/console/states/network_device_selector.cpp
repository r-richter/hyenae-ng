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

#include "../../../../include/os.h"
#include "../../../../include/assert.h"
#include "../../../../include/model/outputs/no_output.h"
#include "../../../../include/model/outputs/file_output.h"
#include "../../../../include/frontend/console/states/network_device_selector.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    network_device_selector::network_device_selector(
        console_app_state_context* context,
        console_io* console_io,
        output_setup* parent) :
            console_app_state(context, console_io, parent)
    {
        string_t caption;
        vector_t<device_t*> devices_list;
        
        _menu = new console_menu(
            console_io, "Network Device Selection", this, parent);

        // Load devices

        model::outputs::network_output::list_devices(devices_list);

        for (auto device : devices_list)
        {
            add_device(device);
        }
    }

    /*---------------------------------------------------------------------- */

    network_device_selector::~network_device_selector()
    {
        for (auto item : _menu_items)
        {
            delete item.first;
            delete item.second;
        }

        safe_delete(_menu);

    } /* ~network_device_selector */

    /*---------------------------------------------------------------------- */

    bool network_device_selector::run()
    {
        string_t path;

        ((output_setup*)get_parent())->update_network_output();

        _menu->set_start_state(get_start_state());

        console_menu::item* choice = _menu->prompt();

        if (choice != _menu->get_start_state_item() &&
            choice != _menu->get_parent_state_item() &&
            choice != NULL)
        {
            _menu->select_all(false);
            choice->set_selected(true);

            _device = _menu_items[choice];
            _selected_item = choice;
        }
        
        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    network_device_selector::device_t*
        network_device_selector::get_device() const
    {
        return _device;

    } /* get_output */

    /*---------------------------------------------------------------------- */

    console_menu::item* network_device_selector::add_device(device_t* device)
    {
        console_menu::item* menu_item = NULL;

        menu_item = new console_menu::item(device->get_description());

        _menu_items[menu_item] = device;
        _menu->add_item(menu_item);

        // Set first device as default
        if (_device == NULL)
        {
            menu_item->set_selected(true);
            _device = device;
        }
        
        return menu_item;

    } /* add_output */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
