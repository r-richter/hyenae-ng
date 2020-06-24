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

#include "../../../include/frontend/console/console_app_config.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    const string_t console_app_config::SECTION_FRONTEND = "frontend";

    /*---------------------------------------------------------------------- */

    const string_t console_app_config::VALUE_TERMINAL_COLORS =
        "terminal_colors";
    
    const string_t console_app_config::VALUE_LINE_CHARACTERS =
        "line_characters";

    /*---------------------------------------------------------------------- */

    console_app_config::console_app_config(
        file_io::provider file_io_provider, const string_t& filename) :
            app_config(file_io_provider, filename) {}

    /*---------------------------------------------------------------------- */

    bool console_app_config::is_terminal_colors_on()
    {
        return get_or_create_frontend_section()->
            get_or_create_value(VALUE_TERMINAL_COLORS, "on")->
                get_value() == "on";

    } /* is_terminal_colors_on */

    /*---------------------------------------------------------------------- */

    void console_app_config::set_terminal_colors_on(bool is_on)
    {
        get_or_create_frontend_section()->
            get_or_create_value(VALUE_TERMINAL_COLORS, is_on ? "on" : "off");

    } /* set_terminal_colors_on */

    /*---------------------------------------------------------------------- */

    bool console_app_config::is_line_characters_on()
    {
        return get_or_create_frontend_section()->
            get_or_create_value(VALUE_LINE_CHARACTERS, "on")->
                get_value() == "on";

    } /* is_line_characters_on */

    /*---------------------------------------------------------------------- */

    void console_app_config::set_line_characters_on(bool is_on)
    {
        get_or_create_frontend_section()->
            get_or_create_value(VALUE_LINE_CHARACTERS, is_on ? "on" : "off");

    } /* set_line_characters_on */

    /*---------------------------------------------------------------------- */

    void console_app_config::restore_defaults()
    {
        // Trigger default value initialization by
        // simply calling their getters.

        is_terminal_colors_on();
        is_line_characters_on();

    } /* restore_defaults */

    /*---------------------------------------------------------------------- */

    console_app_config::section_t*
        console_app_config::get_or_create_frontend_section()
    {
        return get_root_section()->
            get_or_create_sub_section(SECTION_FRONTEND);

    } /* get_or_create_frontend_section */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */
