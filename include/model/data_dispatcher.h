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

#ifndef DATA_DISPATCHER_H
#define DATA_DISPATCHER_H

#include "../observable.h"
#include "data_output.h"
#include "data_generator.h"
#include "duration_generator.h"
#include "dispatcher_listener.h"

namespace hyenae::model
{
	/*---------------------------------------------------------------------- */

	class data_dispatcher :
		public observable<dispatcher_listener>
	{
		public:
			enum class state
			{
				STOPPED,
				RUNNING,
				PAUSED

			}; /* state */

			class stats
			{
				friend class data_dispatcher;

				private:
					size_t _byte_count;
					size_t _packet_count;
					duration_t _duration;
					stats();

				public:
					size_t get_byte_count() const;
					size_t get_packet_count() const;
					duration_t get_duration() const;
					void reset();

			}; /* stats */

			class limits
			{
				public:
					static const size_t SIZE_UNLIMITED = 0;
					static const duration_t DURATION_UNLIMITED;

				private:
					size_t _byte_limit;
					size_t _packet_limit;
					duration_t _duration_limit;

				public:
					limits(
						size_t byte_limit,
						size_t packet_limit,
						duration_t duration_limit);

					bool has_byte_limit() const;
					size_t get_byte_limit() const;
					bool has_packet_limit() const;
					size_t get_packet_limit() const;
					bool has_duration_limit() const;
					duration_t get_duration_limit() const;
					
			}; /* limits */

		private:
			const long long START_TIMEOUT = 3000;

			data_output* _output;
			data_generator* _generator;
			duration_generator* _delay;
			limits* _limits;
			volatile state _state = state::STOPPED;
			stats _stats;
			thread_t* _thread = NULL;

		public:
			data_dispatcher(
				data_output* output,
				data_generator* generator,
				duration_generator* delay = NULL,
				limits* limits = NULL);

			~data_dispatcher();
			state get_state() const;
			const stats* get_stats() const;
			bool is_stopped() const;
			bool is_running() const;
			bool is_paused() const;
			void start(bool wait_for_start = false);
			void pause();
			void resume();
			void stop();

		private:
			void set_state(state state);
			void state_changed();
			static void thread_proc(void* param);
			void dispatcher_loop();
			bool is_limit_reached() const;
			void limit_reached();
			void thread_exception(const exception_t& exception);
			void stats_changed();

	}; /* data_dispatcher */

	/*---------------------------------------------------------------------- */

} /* hyenae::model */

#endif /* DATA_DISPATCHER_H */
