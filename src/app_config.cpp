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

#include "../include/app_config.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    string_t app_config::DEFAULT_FILENAME = "./hyenae.conf";

    /*---------------------------------------------------------------------- */

    app_config::app_config(
        file_io::provider file_io_provider,
        const string_t& filename = DEFAULT_FILENAME) :
            config("hyenae")
    {
        _file_io = file_io_provider();
        _filename = filename;

        restore_defaults();
        
    } /* app_config */

    /*---------------------------------------------------------------------- */
    
    app_config::~app_config()
    {
        if (_file_io != NULL)
        {
            _file_io->close();
        }
        
        safe_delete(_file_io);

    } /* ~app_config() */

    /*---------------------------------------------------------------------- */

    void app_config::restore_defaults()
    {
        get_root_section()->clear();

        config::section* frontend =
            get_root_section()->add_sub_section("frontend");

        config::section* console =
            frontend->add_sub_section("console");

        frontend->add_value("terminal_colors", "on");
        frontend->add_value("line_characters", "on");

    } /* restore_defaults */

    /*---------------------------------------------------------------------- */

    void app_config::load()
    {
        try
        {
            _file_io->open(_filename, false);
            parse_and_replace_root_section(_file_io->read_all());
            _file_io->close();
        }
        catch (const exception_t& exception)
        {
            _file_io->close();

            throw runtime_error_t(exception.what());
        }
        
    } /* load */

    /*---------------------------------------------------------------------- */

    void app_config::save()
    {
        try
        {
            _file_io->open(_filename, false);
            _file_io->write(to_string());
            _file_io->close();
        }
        catch (const exception_t& exception)
        {
            _file_io->close();

            throw runtime_error_t(exception.what());
        }

    } /* save */

    /*---------------------------------------------------------------------- */

} /* hyenae */
