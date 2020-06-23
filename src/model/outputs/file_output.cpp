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
#include "../../../include/model/outputs/file_output.h"

namespace hyenae::model::outputs
{
    /*---------------------------------------------------------------------- */

    file_output::file_output(
        file_io::provider file_io_provider,
        const string_t& path)
    {
        _file_io = file_io_provider();
        _path = path;

    } /* file_output */

    /*---------------------------------------------------------------------- */

    file_output::~file_output()
    {
        close();

        safe_delete(_file_io);
    }

    /*---------------------------------------------------------------------- */

    void file_output::open()
    {
        assert::legal_call(!_file_io->is_open(), "", "already open");

        _file_io->open(_path, true);

    } /* open */

    /*---------------------------------------------------------------------- */

    void file_output::close() noexcept
    {
        _file_io->close();

    } /* close */

    /*---------------------------------------------------------------------- */

    void file_output::send(byte_t* data, size_t size)
    {
        assert::legal_call(_file_io->is_open(), "", "not open");
        assert::argument_not_null(data, "data");
        assert::in_range(size > 0, "size");

        _file_io->write(data, size);

    } /* send */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::outputs */
