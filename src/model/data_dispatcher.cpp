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

#include "../../include/assert.h"
#include "../../include/stop_watch.h"
#include "../../include/model/data_dispatcher.h"

#include <cstdlib>
#include <cstring>

namespace hyenae::model
{
    /*---------------------------------------------------------------------- */

    data_dispatcher::data_dispatcher(
        data_output* output,
        data_generator* generator,
        duration_generator* delay,
        limits* limits)
    {
        assert::argument_not_null(output, "", "No output assigned");
        assert::argument_not_null(generator, "", "No generator assigned");

        _output = output;
        _generator = generator;
        _delay = delay;
        _limits = limits;

    } /* data_dispatcher */

    /*---------------------------------------------------------------------- */

    data_dispatcher::~data_dispatcher()
    {
        stop();

    } /* ~data_dispatcher */

    /*---------------------------------------------------------------------- */

    data_dispatcher::state data_dispatcher::get_state() const
    {
        return _state;

    } /* get_state */

    /*---------------------------------------------------------------------- */

    const data_dispatcher::stats* data_dispatcher::get_stats() const
    {
        return &_stats;

    } /* get_stats */

    /*---------------------------------------------------------------------- */

    bool data_dispatcher::is_stopped() const
    {
        return _state == state::STOPPED;

    } /* is_stopped */

    /*---------------------------------------------------------------------- */

    bool data_dispatcher::is_running() const
    {
        return _state != state::STOPPED;

    } /* is_running */

    /*---------------------------------------------------------------------- */

    bool data_dispatcher::is_paused() const
    {
        return _state == state::PAUSED;

    } /* is_paused */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::start(bool wait_for_start)
    {
        assert::legal_call(is_stopped(), "", "allready started");

        _thread = new thread_t(data_dispatcher::thread_proc, this);

        if (wait_for_start)
        {
            assert::in_time([this]()
            {
                return is_running();

            }, START_TIMEOUT);
        }
        
    } /* start */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::pause()
    {
        if (is_running())
        {
            set_state(state::PAUSED);
        }

    } /* pause */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::resume()
    {
        if (is_paused())
        {
            set_state(state::RUNNING);
        }

    } /* resume */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::stop()
    {
        set_state(state::STOPPED);

        if (_thread != NULL)
        {
            _thread->join();

            safe_delete(_thread);
        }

    } /* stop */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::set_state(state state)
    {
        if (_state != state)
        {
            _state = state;

            state_changed();
        }

    } /* set_state */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::state_changed()
    {
        listeners([](auto listener)
        {
            listener->on_state_changed();
        });

    } /* state_changed */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::thread_proc(void* param)
    {
        ((data_dispatcher*)param)->dispatcher_loop();

    } /* run_thread_proc */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::dispatcher_loop()
    {
        byte_t* data = NULL;
        size_t data_size = 0;
        duration_t time_to_wait = duration_t{ 0 };
        stop_watch delay_watch;
        stop_watch duration_watch;

        try
        {
            _stats.reset();

            if (_delay != NULL)
            {
                _delay->reset();
            }

            set_state(state::RUNNING);

            _output->open();

            data_size = _generator->size();
            data = (byte_t*)malloc(data_size);
            memset(data, 0, data_size);

            duration_watch.start();

            while (is_running())
            {
                if (!is_paused() &&
                    delay_watch.get_time_passed() >= time_to_wait)
                {
                    _generator->to_buffer(data, data_size);
                    _output->send(data, data_size);

                    _stats._byte_count += data_size;
                    _stats._packet_count += 1;

                    _generator->next();

                    if (_delay != NULL)
                    {
                        time_to_wait = _delay->next();
                        delay_watch.start();
                    }
                }

                _stats._duration = duration_watch.get_time_passed();

                stats_changed();

                if (is_limit_reached())
                {
                    limit_reached();

                    break;
                }
            }
        }
        catch (const exception_t& exception)
        {
            thread_exception(exception);
        }

        if (data != NULL)
        {
            free(data);
        }

        _output->close();

        _state = state::STOPPED;

    } /* dispatcher_loop */

    /*---------------------------------------------------------------------- */

    bool data_dispatcher::is_limit_reached() const
    {
        if (_limits != NULL)
        {
            return
                (_limits->has_byte_limit() &&
                 _stats._byte_count >= _limits->get_byte_limit()) ||
                (_limits->has_packet_limit() &&
                 _stats._packet_count >= _limits->get_packet_limit()) ||
                (_limits->has_duration_limit() &&
                 _stats._duration >= _limits->get_duration_limit());
        }

        return false;

    } /* is_limit_reached */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::limit_reached()
    {
        listeners([](auto listener)
        {
            listener->on_limit_reached();
        });

    } /* limit_reached */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::thread_exception(const exception_t& exception)
    {
        listeners([exception](auto listener)
            {
                listener->on_thread_exception(exception);
            });

    } /* thread_exception */

    /*---------------------------------------------------------------------- */

    void data_dispatcher::stats_changed()
    {
        listeners([](auto listener)
        {
            listener->on_stats_changed();
        });

    } /* stats_updated */

    /*---------------------------------------------------------------------- */

} /* hyenae::model */
