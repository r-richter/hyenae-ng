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

#ifndef TO_REVERSE_ORDER_H
#define TO_REVERSE_ORDER_H

#include "../data_transformation.h"

namespace hyenae::model::data_transformations
{
	/*---------------------------------------------------------------------- */

	class to_reverse_order :
		public data_transformation
	{
		private:
			static to_reverse_order* _instance;

		public:
			static to_reverse_order* get_instance();
			size_t result_size(size_t data_size) const;
			byte_t* transform(byte_t* data, size_t size) const;

	}; /* to_reverse_order */

	/*---------------------------------------------------------------------- */

} /* hyenae::model::data_transformations */

#endif /* TO_REVERSE_ORDER_H */
