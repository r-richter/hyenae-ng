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

#include "../../include/model/data_dispatcher.h"

#include <cstring>

namespace hyenae::model
{
	/*---------------------------------------------------------------------- */

	data_dispatcher::stats::stats()
	{
		reset();

	} /* stats */

	/*---------------------------------------------------------------------- */

	size_t data_dispatcher::stats::get_byte_count() const
	{
		return _byte_count;

	} /* get_byte_count */

	/*---------------------------------------------------------------------- */

	size_t data_dispatcher::stats::get_packet_count() const
	{
		return _packet_count;

	} /* get_packet_count */

	/*---------------------------------------------------------------------- */

	duration_t data_dispatcher::stats::get_duration() const
	{
		return _duration;

	} /* get_duration */

	/*---------------------------------------------------------------------- */

	void data_dispatcher::stats::reset()
	{
		memset(this, 0, sizeof(stats));

	} /* reset */

	/*---------------------------------------------------------------------- */

} /* hyenae::model */
