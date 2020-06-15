/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
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

#include "../../../include/frontend/console/console_menu.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    console_menu::item::item() :
        item("Unnamed Item") {}

    /*---------------------------------------------------------------------- */

    console_menu::item::item(
        const string_t& caption, const string_t& hint, const string_t& info)
    {
        _selected = false;
        _caption = caption;
        _hint = hint;
        _info = info;

    } /* item */

    /*---------------------------------------------------------------------- */

    bool console_menu::item::is_selected() const
    {
        return _selected;

    } /* is_selected */

    /*---------------------------------------------------------------------- */

    void console_menu::item::set_selected(bool selected)
    {
        _selected = selected;

    } /* set_selected */

    /*---------------------------------------------------------------------- */

    string_t console_menu::item::get_caption() const
    {
        return _caption;

    } /* get_caption */

    /*---------------------------------------------------------------------- */

    void console_menu::item::set_caption(const string_t& caption)
    {
        _caption = caption;

    } /* set_caption */

    /*---------------------------------------------------------------------- */

    string_t console_menu::item::get_hint() const
    {
        return _hint;

    } /* get_hint */

    /*---------------------------------------------------------------------- */

    void console_menu::item::set_hint(string_t hint)
    {
        _hint = hint;

    } /* set_hint */

    /*---------------------------------------------------------------------- */

    string_t console_menu::item::get_info() const
    {
        return _info;

    } /* get_info */

    void console_menu::item::set_info(string_t info)
    {
        _info = info;

    } /* set_info */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */
