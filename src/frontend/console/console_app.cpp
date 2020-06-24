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
#include "../../../include/frontend/console/console_app.h"
#include "../../../include/frontend/console/states/main_menu.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    console_app::console_app(
        console_app_config* config,
        console_io* console_io,
        file_io::provider file_io_provider)
    {
        assert::argument_not_null(config, "config");
        assert::argument_not_null(console_io, "console_io");

        _config = config;
        _console_io = console_io;
        _file_io_provider = file_io_provider;

    } /* console_app */

    /*---------------------------------------------------------------------- */

    int console_app::run(int argc, char** argv)
    {
        states::main_menu main_menu(
            this,
            _config,
            _console_io,
            _file_io_provider);

        console_app_state_context::run(&main_menu);

        return 0;

    } /* run */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */
