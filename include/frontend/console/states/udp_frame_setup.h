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

#ifndef UDP_FRAME_SETUP_H
#define UDP_FRAME_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/ip_frame_setup.h"
#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/model/generators/protocols/udp_frame_generator.h"

namespace hyenae::frontend::console::states
{
	/*---------------------------------------------------------------------- */

	class udp_frame_setup :
		public generator_setup
	{
		using udp_frame_generator_t =
			model::generators::protocols::udp_frame_generator;

		private:
			static const uint8_t PROTOCOL = 17;

			ip_frame_setup* _ip_frame_setup;
			console_menu* _menu = NULL;
			console_menu::item* _src_port_pattern_item = NULL;
			console_menu::item* _dst_port_pattern_item = NULL;
			console_menu::item* _payload_item = NULL;
			console_menu::item* _back_item = NULL;
			data_generator_t* _generator = NULL;
			string_t _src_port_pattern;
			string_t _dst_port_pattern;
			generator_selector* _payload = NULL;

		public:
			udp_frame_setup(
				console_app_state_context* context,
				console_io* console_io,
				console_app_state* parent,
				ip_frame_setup* ip_frame_setup);

			~udp_frame_setup();
			bool run();
			string_t get_generator_name() const;
			data_generator_t* get_generator() const;
			void update_generator();

		protected:
			void on_select();

		private:
			void update_menu_items();
			void prompt_src_port_pattern();
			void prompt_dst_port_pattern();
			
			void update_generator(
				string_t src_port_pattern,
				string_t dst_port_pattern);

	}; /* udp_frame_setup */

	/*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* UDP_FRAME_SETUP_H */
