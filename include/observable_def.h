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

#ifndef OBSERVABLE_DEF_H
#define OBSERVABLE_DEF_H

#include "common.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    template <class T>
    class observable
    {
        private:
            vector_t<T*> _listeners;

        public:
            void add_listener(T* listener);
            void remove_listener(T* listener);
            
        protected:
            void listeners(func_t<void (T*)> action);

    }; /* observable */

    /*---------------------------------------------------------------------- */

} /* hyenae */

#endif /* OBSERVABLE_DEF_H */
