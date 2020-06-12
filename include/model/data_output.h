/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
 *   Homepage : http://sourceforge.net/projects/hyenae-ng/
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

#ifndef DATA_OUTPUT_H
#define DATA_OUTPUT_H

#include "../common.h"

namespace hyenae::model
{
	/*---------------------------------------------------------------------- */

	class data_output
	{
		public:
			virtual ~data_output() {}
			virtual void open() = 0;
			virtual void close() noexcept = 0;
			virtual void send(byte_t* data, size_t size) = 0;

	}; /* data_output */

	/*---------------------------------------------------------------------- */

} /* hyenae::model */

#endif /* DATA_OUTPUT_H */
