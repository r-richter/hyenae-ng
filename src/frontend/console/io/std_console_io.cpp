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

#include "../../../../include/os.h"
#include "../../../../include/frontend/console/io/std_console_io.h"

#include <iostream>
#include <cstdarg>

#ifdef OS_WINDOWS
    #include <conio.h>
#else
    #include <stdio.h>
    #include <sys/ioctl.h>
    #include <sys/select.h>
    #include <termios.h>
#endif


namespace hyenae::frontend::console::io
{
    /*---------------------------------------------------------------------- */

    std_console_io* std_console_io::_instance = NULL;

    /*---------------------------------------------------------------------- */

    std_console_io* std_console_io::get_instance()
    {
        if (_instance == NULL)
        {
            _instance = new std_console_io();
        }

        return _instance;

    } /* get_instance */

    /*---------------------------------------------------------------------- */

    bool std_console_io::was_key_pressed()
    {
        bool result = false;

        #ifdef OS_WINDOWS
            if ((result = _kbhit()))
            {
                // Prevent overhang input such as when
                // return is pressed.

                _getch();
            }
        #else

            /*
             * Linux (POSIX) implementation of _kbhit().
             * Morgan McGuire, morgan@cs.brown.edu
             */

            static const int STDIN = 0;
            static bool initialized = false;

            if (!initialized)
            {
                // Use termios to turn off line buffering
                termios term;
                tcgetattr(STDIN, &term);
                term.c_lflag &= ~ICANON;
                tcsetattr(STDIN, TCSANOW, &term);
                setbuf(stdin, NULL);
                initialized = true;
            }

            int bytes_waiting;
            ioctl(STDIN, FIONREAD, &bytes_waiting);

            // TODO: Prevent overhang input...

            result = bytes_waiting;
        #endif

        return result;

    } /* was_key_pressed */

    /*---------------------------------------------------------------------- */

    void std_console_io::out(string_t out)
    {
        printf("%s", out.c_str());

    } /* out */

    /*---------------------------------------------------------------------- */

    string_t std_console_io::in()
    {
        string_t input;

        std::getline(std::cin, input);

        return input;

    } /* in */

    /*---------------------------------------------------------------------- */

    void std_console_io::clear()
    {
        #ifdef OS_WINDOWS
            std::system("cls");
        #else
            std::system("clear");
        #endif

    } /* clear */
    
    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::io */
