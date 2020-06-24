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

#include "../../../include/app_config.h"
#include "../../../include/io/std_file_io.h"
#include "../../../include/frontend/console/console_app.h"
#include "../../../include/frontend/console/io/std_console_io.h"

/*---------------------------------------------------------------------- */

int main(int argc, char** argv)
{
    using namespace hyenae::frontend::console;
    
    hyenae::app_config config(hyenae::io::std_file_io::PROVIDER);

    try
    {
        config.load_or_create();
    }
    catch (const exception_t& exception)
    {
        // TODO: Error message...

        config.restore_defaults();
    }

    return (
        new console_app(
            &config,
            io::std_console_io::get_instance(),
            hyenae::io::std_file_io::PROVIDER))->run(argc, argv);

} /* main */

/*---------------------------------------------------------------------- */
