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

#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include "common.h"

namespace hyenae
{
	/*---------------------------------------------------------------------- */

	class stop_watch
	{
		using clock_t = std::chrono::system_clock;

		private:
			duration_t _started_at;
			duration_t _stopped_at;

		public:
			stop_watch();
			duration_t get_time_passed() const;
			void start();
			void stop();
			void reset();

	}; /* stop_watch */

	/*---------------------------------------------------------------------- */

} /* hyenae */

#endif /* STOP_WATCH_H */
