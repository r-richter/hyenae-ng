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

#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include "../../../include/file_io.h"
#include "../../../include/app_config.h"
#include "../../../include/frontend/console/console_io.h"
#include "../../../include/frontend/console/console_app_state.h"
#include "../../../include/frontend/console/console_app_state_context.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    class console_app :
        public console_app_state_context
    {
        private:
            app_config* _config;
            console_io* _console_io;
            file_io::provider _file_io_provider;

        public:
            console_app(
                app_config* config,
                console_io* console_io,
                file_io::provider file_io_provider);

            int run(int argc, char** argv);

    }; /* console_app */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */

#endif /* CONSOLE_APP_H */
