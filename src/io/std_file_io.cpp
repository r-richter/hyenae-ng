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

#include "../include/assert.h"
#include "../include/io/std_file_io.h"

namespace hyenae::io
{
    /*---------------------------------------------------------------------- */

    const file_io::provider std_file_io::PROVIDER = [] ()
    {
        return new std_file_io();
    };

    /*---------------------------------------------------------------------- */

    bool std_file_io::is_open() const
    {
        return _stream.is_open();

    } /* is_open */

    /*---------------------------------------------------------------------- */

    void std_file_io::open(const string_t& filename, bool overwrite)
    {
        assert::legal_call(!is_open(), "", "already open");

        _stream.open(
            filename, overwrite ? std::ios_base::trunc : std::ios_base::app);

    } /* open */

    /*---------------------------------------------------------------------- */

    void std_file_io::close() noexcept
    {
        _stream.close();

    } /* close */

    /*---------------------------------------------------------------------- */

    void std_file_io::write(const string_t& content)
    {
        assert::legal_call(is_open(), "", "not open");

        _stream.write(content.c_str(), content.size());

    } /* write */

    /*---------------------------------------------------------------------- */

    void std_file_io::write(byte_t* data, size_t size)
    {
        assert::legal_call(is_open(), "", "not open");
        
        _stream.write((const char*)data, size);

    } /* write */

    /*---------------------------------------------------------------------- */

    string_t std_file_io::read_all()
    {
        assert::legal_call(is_open(), "", "not open");

        return string_t(
            std::istreambuf_iterator<char>(_stream),
            std::istreambuf_iterator<char>());
            
    } /* read_all */

    /*---------------------------------------------------------------------- */

} /* hyenae::io */
