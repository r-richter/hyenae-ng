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

#include "../../../include/assert.h"
#include "../../../include/frontend/console/console_menu.h"

#include <string>

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    console_menu::console_menu(
        console_io* console_io,
        const string_t& title,
        console_app_state* parent_state)
    {
        assert::argument_not_null(console_io, "console_io");

        _console_io = console_io;
        _parent_state = parent_state;

        _title = title;
        _error_message = "";
        _info_message = "";
        _last_error = "";

        _parent_state_item = new item(parent_state != NULL ? "Back" : "Exit");
        _parent_state_item->set_choice(".");

    } /* console_menu */

    /*---------------------------------------------------------------------- */

    console_menu::~console_menu()
    {
        safe_delete(_parent_state_item);

    } /* ~console_menu */

    /*---------------------------------------------------------------------- */

    void console_menu::add_item(item* item)
    {
        _items.push_back(item);

        item->set_choice(std::to_string(_items.size()));

    } /* add_option */

    /*---------------------------------------------------------------------- */

    console_menu::item* console_menu::prompt(item* default_choice)
    {
        _console_io->header_out(_title);

        for (size_t pos = 0; pos < _items.size(); pos++)
        {
            item_out(_items[pos], false);
        }

        item_out(_parent_state_item, true);

        if (_error_message != "")
        {
            _console_io->error_out(_error_message, true);
        }

        if (_info_message != "")
        {
            _console_io->info_out(_info_message, true);
        }
        
        return choice_in(default_choice);

    } /* prompt */

    /*---------------------------------------------------------------------- */

    void console_menu::select_all(bool selected)
    {
        for (auto item : _items)
        {
            item->set_selected(selected);
        }

    } /* select_all */

    /*---------------------------------------------------------------------- */

    string_t console_menu::get_info_message() const
    {
        return _info_message;

    } /* get_info_message */

    /*---------------------------------------------------------------------- */

    void console_menu::set_info_message(string_t message)
    {
        _info_message = message;

    } /* set_info_message */

    /*---------------------------------------------------------------------- */

    string_t console_menu::get_error_message() const
    {
        return _error_message;

    } /* get_error_message */

    /*---------------------------------------------------------------------- */

    void console_menu::set_error_message(string_t message)
    {
        _error_message = message;

    } /* set_error_message */

    /*---------------------------------------------------------------------- */

    void console_menu::item_out(
        item* item, bool nl_before)
    {
        _console_io->menu_item_out(
            item->get_choice(),
            item->is_selected(),
            item->get_caption(),
            item->get_hint(),
            item->get_info(),
            _items.size() + 1,
            nl_before);

    } /* item_out */

    /*---------------------------------------------------------------------- */

    console_menu::item* console_menu::choice_in(item* default_choice)
    {
        string_t input;
        string_t hint = "";

        if (_last_error != "")
        {
            _console_io->error_out(_last_error, true);
        }

        _last_error = "";

        if (default_choice != NULL)
        {
            hint = default_choice->get_choice();
        }

        _console_io->separator_out(true, false);

        input = _console_io->prompt("Enter Selection", hint);

        if (input == "" && default_choice != NULL)
        {
            input = default_choice->get_choice();
        }

        if (input != _parent_state_item->get_choice())
        {
            for (auto item : _items)
            {
                if (item->get_choice() == input)
                {
                    return item;
                }
            }

            _last_error = concat(
                "Invalid option: ", input.c_str());
        }
        else
        {
            if (_parent_state != NULL)
            {
                _parent_state->enter();
            }
        }

        return NULL;

    } /* choice_in */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */
