/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
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

#ifndef TEXT_BUFFER_SETUP_H
#define TEXT_BUFFER_SETUP_H

#include "../../../../include/frontend/console/console_menu.h"
#include "../../../../include/frontend/console/states/generator_setup.h"
#include "../../../../include/model/generators/string_generator.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class text_buffer_setup :
        public generator_setup
    {
        using string_generator_t = model::generators::string_generator;

        private:
            console_menu* _menu = NULL;
            console_menu::item* _text_item = NULL;
            console_menu::item* _back_item = NULL;
            data_generator_t* _generator = NULL;
            string_t _text;

        public:
            text_buffer_setup(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent);

            ~text_buffer_setup();
            bool run();
            string_t get_generator_name() const;
            data_generator_t* get_generator() const;
            void update_generator();

        protected:
            void on_select() {};

        private:
            void update_menu_items();
            void prompt_text();
            void update_generator(string_t text);

    }; /* text_buffer_setup */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* TEXT_BUFFER_SETUP_H */
