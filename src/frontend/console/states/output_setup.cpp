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
#include "../../../../include/frontend/console/states/output_setup.h"

#ifdef OS_POSIX
    #include <unistd.h>
#endif

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    const char* output_setup::FILE_OUTPUT_PATH = "./hyenae.dump";

    /*---------------------------------------------------------------------- */

    output_setup::output_setup(
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent) :
            console_app_state(context, console_io, parent)
    {
        string_t caption;
        
        _menu = new console_menu(console_io, "Output Setup");

        // Default values
        _file_path = FILE_OUTPUT_PATH;
        _network_device_error = "";

        try
        {
            // Init network devices

            #ifdef OS_POSIX
                assert::legal_state(
                    getuid() == 0, "", "network access denied, no root user");
            #endif

            model::outputs::network_output::list_devices(_network_devices);
            _network_device = _network_devices.front();
        }
        catch (const exception_t& exception)
        {
            _network_device_error = exception.what();
        }
        
        // No Output
        add_output("No Output", new model::outputs::no_output());

        // Send To File
        _file_output_item = add_output("File System", NULL);

        // Send To Network
        if (_network_devices.size() > 0)
        {
            _network_output_item = add_output("Network Adapter", NULL);
        }
        
        // Back
        _back_item = new console_menu::item("Back");
        _menu->add_item(_back_item);
    }

    /*---------------------------------------------------------------------- */

    output_setup::~output_setup()
    {
        for (auto item : _menu_items)
        {
            delete item.first;
            delete item.second;
        }

        if (_network_devices.size() > 0)
        {
            for (auto item : _network_devices)
            {
                delete item;
            }
        }

        safe_delete(_menu);
        safe_delete(_back_item);

    } /* ~output_setup */

    /*---------------------------------------------------------------------- */

    bool output_setup::run()
    {
        string_t path;
        data_output_t* output = NULL;

        update_menu_items();

        _menu->set_error_message(_network_device_error);

        console_menu::item* choice = _menu->prompt(_selected_item);

        if (choice != NULL)
        {
            if (choice != _back_item)
            {
                _menu->select_all(false);

                _file_output_item->set_hint("");
                _network_output_item->set_hint("");

                choice->set_selected(true);

                output = _menu_items[choice];

                if (choice == _file_output_item)
                {
                    _file_output_item->set_hint("...");

                    _output = select_file_output(_selected_item == choice);
                }
                else if (choice == _network_output_item)
                {
                    _network_output_item->set_hint("...");

                    _output = select_network_output(_selected_item == choice);
                }
                else
                {
                    _output = output;
                }

                _selected_item = choice;
            }
            else
            {
                back();
            }
        }
        
        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    model::data_output* output_setup::get_output() const
    {
        return _output;

    } /* get_output */

    /*---------------------------------------------------------------------- */

    void output_setup::update_menu_items()
    {
        _file_output_item->set_info(_file_path);

        if (_network_output_item != NULL)
        {
            _network_output_item->set_info(
                _network_device->get_description());
        }

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    console_menu::item* output_setup::add_output(
        string_t caption, data_output_t* output)
    {
        console_menu::item* menu_item = NULL;

        menu_item = new console_menu::item(caption);

        _menu_items[menu_item] = output;
        _menu->add_item(menu_item);

        // Set first output as default
        if (_output == NULL)
        {
            menu_item->set_selected(true);
            _output = output;
        }
        
        return menu_item;

    } /* add_output */

    /*---------------------------------------------------------------------- */

    output_setup::data_output_t* output_setup::select_file_output(
        bool setup)
    {
        safe_delete(_menu_items[_file_output_item]);

        if (setup)
        {
            _file_path = get_console()->prompt(
                "Enter Path", _file_path, _file_path);
        }
        
        _menu_items[_file_output_item] =
            new model::outputs::file_output(_file_path);

        return _menu_items[_file_output_item];

    } /* select_file_output */

    /*---------------------------------------------------------------------- */

    output_setup::data_output_t* output_setup::select_network_output(
        bool setup)
    {
        vector_t<string_t> device_list;

        safe_delete(_menu_items[_network_output_item]);

        if (setup)
        {
            for (auto device : _network_devices)
            {
                device_list.push_back(device->get_description());
            }

            size_t choice =
                get_console()->prompt_list_choice(device_list);

            _network_device = _network_devices.at(choice);
        }

        _menu_items[_network_output_item] =
            new model::outputs::network_output(_network_device);

        return _menu_items[_network_output_item];

    } /* select_network_output */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
