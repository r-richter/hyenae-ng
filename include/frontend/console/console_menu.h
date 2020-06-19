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

#ifndef CONSOLE_MENU_H
#define CONSOLE_MENU_H

#include "console_io.h"
#include "console_app_state.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    class console_menu
    {
        public:
            class item
            {
                friend class console_menu;

                private:
                    bool _selected;
                    string_t _caption;
                    string_t _hint;
                    string_t _info;

                public:
                    item();
                    
                    item(
                        const string_t& caption,
                        const string_t& hint = "",
                        const string_t& info = "");
                    
                    bool is_selected() const;
                    void set_selected(bool selected);
                    string_t get_caption() const;
                    void set_caption(const string_t& caption);
                    string_t get_hint() const;
                    void set_hint(string_t hint);
                    string_t get_info() const;
                    void set_info(string_t info);

            }; /* item */

        private:
            console_io* _console_io;
            console_app_state* _parent_state;
            vector_t<item*> _items;
            item* _parent_state_item = NULL;
            string_t _title;
            string_t _error_message;
            string_t _info_message;
            string_t _last_error;

        public:
            console_menu(
                console_io* console_io,
                const string_t& title,
                console_app_state* parent_state = NULL);

            ~console_menu();
            void add_item(item* item);
            item* prompt(item* default_choice = NULL);
            void select_all(bool selected);
            string_t get_info_message() const;
            void set_info_message(string_t message);
            string_t get_error_message() const;
            void set_error_message(string_t message);
            
        private:
            void item_out(size_t pos, item* item, bool nl_before);
            item* choice_in(item* default_choice);
            size_t item_choice_pos(item* item);

    }; /* console_menu */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */

#endif /* CONSOLE_MENU_H */
