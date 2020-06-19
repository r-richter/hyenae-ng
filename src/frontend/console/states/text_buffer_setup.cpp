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

#include "../../../../include/frontend/console/states/text_buffer_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    text_buffer_setup::text_buffer_setup(
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent) :
        generator_setup(context, console_io, parent)
    {
        _menu = new console_menu(
            console_io, get_generator_name() + " Setup");

        _text = "Test";

        // Text
        _text_item = new console_menu::item("Text");
        _menu->add_item(_text_item);

        update_generator();

    } /* ethernet_frame_setup */

    /*---------------------------------------------------------------------- */

    text_buffer_setup::~text_buffer_setup()
    {
        safe_delete(_menu);
        safe_delete(_text_item);
        safe_delete(_generator);

    } /* ~ethernet_frame_setup */

    /*---------------------------------------------------------------------- */

    bool text_buffer_setup::run()
    {
        update_generator();
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _text_item)
        {
            prompt_text();
        }
        else if (choice == _menu->get_back_item())
        {
            back();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    string_t text_buffer_setup::get_generator_name() const
    {
        return "Text-Buffer";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    text_buffer_setup::data_generator_t*
        text_buffer_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void text_buffer_setup::update_generator()
    {
        update_generator(_text);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void text_buffer_setup::update_menu_items()
    {
        _text_item->set_info(_text);

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void text_buffer_setup::prompt_text()
    {
        _text = get_console()->prompt("Enter Text");

    } /* prompt_text */

    /*---------------------------------------------------------------------- */

    void text_buffer_setup::update_generator(string_t text)
    {
        safe_delete(_generator);

        _generator = new string_generator_t(
            text, string_generator_t::encoding::ASCII);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
