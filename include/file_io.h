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

#ifndef FILE_IO_H
#define FILE_IO_H

#include "common.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

	class file_io
	{
		public:
			using provider = func_t<file_io*()>;

			virtual bool is_open() const = 0;
			virtual void open(const string_t& filename, bool overwrite) = 0;
			virtual void close() noexcept  = 0;
			virtual void write(const string_t& content) = 0;
			virtual string_t read_all() = 0;

	}; /* file_io */

    /*---------------------------------------------------------------------- */

} /* hyenae */

#endif /* FILE_IO_H */
