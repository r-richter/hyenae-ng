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

#ifndef CONSOLE_APP_STATE_H
#define CONSOLE_APP_STATE_H

#include "console_io.h"
#include "console_app_config.h"
#include "console_app_state_context.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    class console_app_state_context;

    class console_app_state
    {
        private:
            console_app_state_context* _context;
            console_app_config* _config;
            console_io* _console_io;
            console_app_state* _parent;

        public:
            console_app_state(
                console_app_state_context* context,
                console_app_config* console_app_config,
                console_io* console_io,
                console_app_state* parent = NULL);

            virtual ~console_app_state() {}
            console_app_state_context* get_context() const;
            console_app_config* get_config() const;
            console_io* get_console() const;
            console_app_state* get_parent() const;
            void enter();
            void enter(console_app_state* parent);
            virtual bool run() = 0;

    }; /* console_app_state */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */

#endif /* CONSOLE_APP_STATE_H */
