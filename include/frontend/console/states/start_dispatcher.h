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

#ifndef START_DISPATCHER_H
#define START_DISPATCHER_H

#include "../../../../include/model/data_output.h"
#include "../../../../include/model/data_generator.h"
#include "../../../../include/model/data_dispatcher.h"
#include "../../../../include/frontend/console/console_app_state.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    class main_menu;

    class start_dispatcher :
        public console_app_state, model::dispatcher_listener
    {
        using data_output_t = hyenae::model::data_output;
        using data_generator_t = hyenae::model::data_generator;
        using data_dispatcher_t = hyenae::model::data_dispatcher;
        using limits_t = hyenae::model::data_dispatcher::limits;
        using delay_t = hyenae::model::duration_generator;

        private:
            const int64_t WARMUP_TIMEOUT = 3000;

            data_output_t* _output = NULL;
            data_generator_t* _generator = NULL;
            limits_t* _limits = NULL;
            delay_t* _delay = NULL;
            data_dispatcher_t* _dispatcher = NULL;
            exception_t* _thread_exception = NULL;

        public:
            start_dispatcher(
                console_app_state_context* context,
                console_io* console_io,
                console_app_state* parent);

            ~start_dispatcher();

            bool run();

            void enter(
                data_output_t* output,
                data_generator_t* generator,
                limits_t* limits,
                delay_t* delay);

        protected:
            void on_state_changed() {};
            void on_stats_changed() {};
            void on_limit_reached() {};
            void on_thread_exception(const exception_t& exception);

        private:
            bool start_screen();
            void result_screen();

    }; /* start_dispatcher */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */

#endif /* START_DISPATCHER_H */
