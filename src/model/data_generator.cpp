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

#include "../../include/assert.h"
#include "../../include/model/data_generator.h"

namespace hyenae::model
{
	/*---------------------------------------------------------------------- */

	size_t data_generator::transformation_count() const
	{
		return _transformations.size();

	} /* transformation_count */

	/*---------------------------------------------------------------------- */

	data_transformation* data_generator::transformation_at(
		const size_t pos) const
	{
		assert::in_range(pos < _transformations.size(), "pos");

		return _transformations.at(pos);

	} /* transformation_at */

	/*---------------------------------------------------------------------- */

	void data_generator::add_transformation(
		data_transformation* transformation)
	{
		assert::argument_not_null(transformation, "transformation");

		_transformations.push_back(transformation);

	} /* add_transformation */

	/*---------------------------------------------------------------------- */

	void data_generator::remove_transformation_at(const size_t pos)
	{
		assert::in_range(pos < _transformations.size());

		_transformations.erase(_transformations.begin() + pos);

	} /* remove_transformation_at */

	/*---------------------------------------------------------------------- */

	size_t data_generator::size() const
	{
		size_t size = data_size();

		for (auto transformation : _transformations)
		{
			size = transformation->result_size(size);
		}

		return size;

	} /* size */

	/*---------------------------------------------------------------------- */

	byte_t* data_generator::to_buffer(byte_t* buffer, size_t size) const
	{
		size_t result_size = 0;
		byte_t* result = NULL;

		assert::argument_not_null(buffer, "buffer");
		assert::no_overflow(size >= this->size());

		result_size = data_size();
		result = (byte_t*)malloc(result_size);
		data_to_buffer(result, result_size);

		for (auto transformation : _transformations)
		{
			result = transformation->transform(result, result_size);
			result_size = transformation->result_size(result_size);
		}

		memcpy(buffer, result, result_size);
		free(result);

		return buffer;

	} /* to_buffer */

	/*---------------------------------------------------------------------- */

	void data_generator::data_changed()
	{
		listeners([](auto listener)
		{
			listener->on_data_changed();
		});

	} /* data_changed */

	/*---------------------------------------------------------------------- */

} /* hyenae::model */
