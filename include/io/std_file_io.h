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

#ifndef STD_FILE_IO_H
#define STD_FILE_IO_H

#include "../file_io.h"

#include <fstream>

namespace hyenae::io
{
    /*---------------------------------------------------------------------- */

	class std_file_io :
		public file_io
	{
		public:
			static const file_io::provider PROVIDER;

		private:
            std::fstream _stream;
			
		public:
			bool is_open() const;
			void open(const string_t& filename, bool overwrite);
			void close() noexcept;
			void write(const string_t& content);
			void write(byte_t* data, size_t size);
			string_t read_all();

	}; /* std_file_io */

    /*---------------------------------------------------------------------- */

} /* hyenae::io */

#endif /* STD_FILE_IO_H */
