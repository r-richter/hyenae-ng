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

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include "../observable.h"
#include "generator_listener.h"
#include "data_transformation.h"

namespace hyenae::model
{
	/*---------------------------------------------------------------------- */

	class data_generator :
		public observable<generator_listener>
	{
		private:
			vector_t<data_transformation*> _transformations;

		public:
			virtual ~data_generator() {}
			size_t transformation_count() const;
			data_transformation* transformation_at(const size_t pos) const;
			void add_transformation(data_transformation* transformation);
			void remove_transformation_at(const size_t pos);
			size_t size() const;
			virtual void next(bool data_changed = true) = 0;
			virtual void reset(bool data_changed = true) = 0;
			byte_t* to_buffer(byte_t* buffer, size_t size) const;

		protected:
			virtual size_t data_size() const = 0;

			virtual byte_t* data_to_buffer(
				byte_t* buffer, size_t size) const = 0;

		protected:
			void data_changed();

	}; /* data_generator */

	/*---------------------------------------------------------------------- */

} /* hyenae::model */

#endif /* DATA_GENERATOR_H */
