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

#ifndef STD_CONSOLE_IO_H
#define STD_CONSOLE_IO_H

#include "../console_io.h"

namespace hyenae::frontend::console::io
{
    /*---------------------------------------------------------------------- */

    class std_console_io :
        public console_io
    {
        private:
            static std_console_io* _instance;

        public:
            static std_console_io* get_instance();
            bool was_key_pressed();

        protected:
            void out(string_t out);
            string_t in();
            void clear();

    }; /* std_console_io */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::io */

#endif /* STD_CONSOLE_IO_H */
