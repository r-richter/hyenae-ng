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

#include "../include/assert.h"
#include "../include/observable_def.h"

#include <algorithm>

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    template <class T>
    void observable<T>::add_listener(T* listener)
    {
        assert::argument_not_null(listener, "listener");
        
        auto pos = std::find(_listeners.begin(), _listeners.end(), listener);

        if (pos == _listeners.end())
        {
            _listeners.push_back(listener);
        }

    } /* add_listener */

    /*---------------------------------------------------------------------- */

    template <class T>
    void observable<T>::remove_listener(T* listener)
    {
        assert::argument_not_null(listener, "listener");

        auto pos = std::find(_listeners.begin(), _listeners.end(), listener);

        if (pos != _listeners.end())
        {
            _listeners.erase(pos);
        }

    } /* remove_listener */

    /*---------------------------------------------------------------------- */

    template <class T>
    void observable<T>::listeners(func_t<void (T*)> action)
    {
        for (auto cur_listener : _listeners)
        {
            action(cur_listener);
        }

    } /* listeners */

    /*---------------------------------------------------------------------- */

} /* hyenae */
