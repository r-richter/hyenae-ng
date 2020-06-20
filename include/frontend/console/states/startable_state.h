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

#ifndef STARTABLE_STATE_H
#define STARTABLE_STATE_H

#include "../console_app_state.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class startable_state
    {
        private:
            console_app_state* _start_state = NULL;

        public:
            console_app_state* get_start_state() const;
            void set_start_state(console_app_state* state);

    }; /* startable_state */

    /*---------------------------------------------------------------------- */

}; /* hyenae::frontend::console::states */

#endif /* STARTABLE_STATE_H */
