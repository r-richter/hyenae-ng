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

#ifndef CONSOLE_APP_CONFIG_H
#define CONSOLE_APP_CONFIG_H

#include "../../app_config.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

	class console_app_config :
        public app_config
	{
        public:
            /* Section names */
            static const string_t SECTION_FRONTEND;

            /* Value names */
            static const string_t VALUE_TERMINAL_COLORS;
            static const string_t VALUE_LINE_CHARACTERS;

        public:
            console_app_config(
                file_io::provider file_io_provider,
                const string_t& filename = DEFAULT_FILENAME);

            /* Frontend settings */
            bool is_terminal_colors_on();
            void set_terminal_colors_on(bool is_on);
            bool is_line_characters_on();
            void set_line_characters_on(bool is_on);

        protected:
            void restore_defaults();

        private:
            section_t* get_or_create_frontend_section();

	}; /* console_app_config */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */

#endif /* CONSOLE_APP_CONFIG_H */
