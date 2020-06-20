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

#include "../../../../include/assert.h"
#include "../../../../include/frontend/console/states/main_menu.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    main_menu::main_menu(
        console_app_state_context* context, console_io* console_io) :
            console_app_state(context, console_io)
    {
        _menu = new console_menu(console_io, "Main Menu", NULL, this);
        
        // Output setup
        _output_setup_item = new console_menu::item("Output Setup");
        _output_setup = new states::output_setup(
            get_context(), console_io, this);
        _menu->add_item(_output_setup_item);

        // Generator setup
        _generator_selector_item = new console_menu::item("Generator Setup");
        _generator_selector = new states::generator_selector(
            "Generator Setup", get_context(), console_io, this);
        _menu->add_item(_generator_selector_item);

        // Dispatcher setup
        _dispatcher_setup = new states::dispatcher_setup(
            get_context(), console_io, this);
        _dispatcher_setup_item = new console_menu::item("Dispatcher Setup");
        _menu->add_item(_dispatcher_setup_item);

        // Start dispatcher
        _start_dispatcher = new states::start_dispatcher(
            get_context(),
            console_io,
            _output_setup,
            _generator_selector,
            _dispatcher_setup);
        _menu->set_start_state(_start_dispatcher);
        _output_setup->set_start_state(_start_dispatcher);
        _generator_selector->set_start_state(_start_dispatcher);
        _dispatcher_setup->set_start_state(_start_dispatcher);

    } /* main_menu */

    /*---------------------------------------------------------------------- */

    main_menu::~main_menu()
    {
        safe_delete(_menu);
        safe_delete(_output_setup_item);
        safe_delete(_generator_selector_item);
        safe_delete(_dispatcher_setup_item);
        safe_delete(_output_setup);
        safe_delete(_generator_selector);
        safe_delete(_dispatcher_setup);
        safe_delete(_start_dispatcher);

    } /* ~main_menu */

    /*---------------------------------------------------------------------- */

    bool main_menu::run()
    {
        console_menu::item* choice = _menu->prompt();

        if (choice == _output_setup_item)
        {
            _output_setup->enter();
        }
        else if (choice == _generator_selector_item)
        {
            _generator_selector->enter();
        }
        else if (choice == _dispatcher_setup_item)
        {
            _dispatcher_setup->enter();
        }
        else if (choice == _menu->get_parent_state_item())
        {
            return get_console()->prompt(
                0, 1, "Confirm Exit", "0 = Abort, 1 = Confirm] [0", 0) == 0;
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
