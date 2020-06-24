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

#ifndef GENERATOR_SETUP_H
#define GENERATOR_SETUP_H

#include "../../../../include/model/data_generator.h"
#include "../../../../include/frontend/console/console_app_state.h"
#include "../../../../include/frontend/console/states/startable_state.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class generator_setup :
        public startable_state,
        public console_app_state
    {
        friend class generator_selector;

        public:
            using data_generator_t = hyenae::model::data_generator;

        public:
            generator_setup(
                console_app_state_context* context,
                console_app_config* config,
                console_io* console_io,
                console_app_state* parent = NULL);

            virtual string_t get_generator_name() const = 0;
            virtual data_generator_t* get_generator() const = 0;
            virtual void update_generator() = 0;

        protected:
            virtual void on_select() = 0;

    }; /* generator_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* GENERATOR_SETUP_H */
