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

    const string_t app_config::SECTION_ROOT = "hyenae";

    /*---------------------------------------------------------------------- */

    const string_t app_config::DEFAULT_FILENAME = "./hyenae.conf";

    /*---------------------------------------------------------------------- */

    app_config::app_config(
        file_io::provider file_io_provider, const string_t& filename)
    {
        _file_io = file_io_provider();
        _filename = filename;
        _config = new config(SECTION_ROOT);

    } /* app_config */

    /*---------------------------------------------------------------------- */

    app_config::~app_config()
    {
        if (_file_io != NULL)
        {
            _file_io->close();
        }

        safe_delete(_file_io);
        safe_delete(_config);

    } /* ~app_config */

    /*---------------------------------------------------------------------- */

    void app_config::load()
    {
        safe_delete(_config);

        try
        {
            _file_io->open(_filename, false);
            _config = config::parse(_file_io->read_all());
            _file_io->close();
        }
        catch (const exception_t& exception)
        {
            _file_io->close();

            throw runtime_error_t(exception.what());
        }

    } /* load */

    /*---------------------------------------------------------------------- */

    void app_config::load_or_restore_defaults()
    {
        safe_delete(_config);

        try
        {
            if (_file_io->exists(_filename))
            {
                _file_io->open(_filename, false);
                _config = config::parse(_file_io->read_all());
                _file_io->close();
            }
            else
            {
                _config = new config(SECTION_ROOT);

                restore_defaults();
                save();
            }
        }
        catch (const exception_t& exception)
        {
            _file_io->close();

            throw runtime_error_t(exception.what());
        }

    } /* load_or_restore_defaults */

    /*---------------------------------------------------------------------- */

    void app_config::save()
    {
        try
        {
            _file_io->open(_filename, true);
            _file_io->write(_config->to_string());
            _file_io->close();
        }
        catch (const exception_t& exception)
        {
            _file_io->close();

            throw runtime_error_t(exception.what());
        }
    } /* save */

    /*---------------------------------------------------------------------- */

    app_config::section_t* app_config::get_root_section()
    {
        return _config->get_root_section();

    } /* get_root_section */

    /*---------------------------------------------------------------------- */

} /* hyenae */
