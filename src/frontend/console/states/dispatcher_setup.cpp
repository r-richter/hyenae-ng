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

#include "../../../../include/assert.h"
#include "../../../../include/frontend/console/states/dispatcher_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    dispatcher_setup::dispatcher_setup(
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent) :
            console_app_state(context, console_io, parent)
    {
        _limits = new limits_t(
            limits_t::SIZE_UNLIMITED,
            limits_t::SIZE_UNLIMITED,
            limits_t::DURATION_UNLIMITED);

        // Default delay
        _delay_type = delay_type::NONE;
        _delay = NULL;

        _menu = new console_menu(console_io, "Dispatcher Setup");

        // Byte Limit
        _byte_limit_item = new console_menu::item("Byte Limit");
        _menu->add_item(_byte_limit_item);

        // Packet Limit
        _packet_limit_item = new console_menu::item("Packet Limit");
        _menu->add_item(_packet_limit_item);

        // Duration Limit
        _duration_limit_item = new console_menu::item("Duration Limit");
        _menu->add_item(_duration_limit_item);

        // Send-Delay
        _send_delay_item = new console_menu::item("Send-Delay");
        _menu->add_item(_send_delay_item);

        // Back
        _back_item = new console_menu::item("Back");
        _menu->add_item(_back_item);
    }

    /*---------------------------------------------------------------------- */

    dispatcher_setup::~dispatcher_setup()
    {
        safe_delete(_menu);
        safe_delete(_byte_limit_item);
        safe_delete(_packet_limit_item);
        safe_delete(_duration_limit_item);
        safe_delete(_send_delay_item);
        safe_delete(_back_item);
        safe_delete(_limits);
        safe_delete(_delay);

    } /* ~dispatcher_setup */

    /*---------------------------------------------------------------------- */

    bool dispatcher_setup::run()
    {
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _byte_limit_item)
        {
            prompt_byte_limit();
        }
        else if (choice == _packet_limit_item)
        {
            prompt_packet_limit();
        }
        else if (choice == _duration_limit_item)
        {
            prompt_duration_limit();
        }
        else if (choice == _send_delay_item)
        {
            prompt_send_delay();
        }
        else if (choice == _back_item)
        {
            back();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    dispatcher_setup::limits_t* dispatcher_setup::get_limits()
    {
        return _limits;

    } /* get_limits */

    /*---------------------------------------------------------------------- */

    dispatcher_setup::delay_t* dispatcher_setup::get_delay()
    {
        return _delay;

    } /* get_delay */

    /*---------------------------------------------------------------------- */

    void dispatcher_setup::update_menu_items()
    {
        string_t delay_info = "";

        // Byte Limit
        if (_limits->has_byte_limit())
        {
            _byte_limit_item->set_info(
                std::to_string(_limits->get_byte_limit()));
        }
        else
        {
            _byte_limit_item->set_info("Off");
        }

        // Packet Limit
        if (_limits->has_packet_limit())
        {
            _packet_limit_item->set_info(
                std::to_string(_limits->get_packet_limit()));
        }
        else
        {
            _packet_limit_item->set_info("Off");
        }

        // Duration Limit
        if (_limits->has_duration_limit())
        {
            _duration_limit_item->set_info(
                to_ms_string(_limits->get_duration_limit()));
        }
        else
        {
            _duration_limit_item->set_info("Off");
        }

        // Set Send-Delay
        switch (_delay_type)
        {
            case delay_type::NONE:
                delay_info = "Off";
                break;

            case delay_type::FIXED:
                delay_info =
                    to_ms_string(((fixed_delay_t*)_delay)->get_duration());
                break;

            case delay_type::RANDOM:
                delay_info.append(
                    std::to_string(
                        to_ms(((random_delay_t*)_delay)->get_min_duration())));
                delay_info.append(" ~ ");
                delay_info.append(
                        to_ms_string(
                        ((random_delay_t*)_delay)->get_max_duration()));
                break;

            default:
                assert::legal_call(false, "", "unknown delay type");
        }

        _send_delay_item->set_info(delay_info);

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void dispatcher_setup::prompt_byte_limit()
    {
        int64_t input = 0;
        limits_t* old_limits = _limits;

        input = get_console()->prompt(
            0, INT32_MAX, "Enter Byte Limit", "0 = Off");

        if (input > 0)
        {
            _limits = new limits_t(
                (size_t) input,
                old_limits->get_packet_limit(),
                old_limits->get_duration_limit());
        }
        else
        {
            _limits = new limits_t(
                limits_t::SIZE_UNLIMITED,
                old_limits->get_packet_limit(),
                old_limits->get_duration_limit());
        }

        safe_delete(old_limits);

    } /* prompt_byte_limit */

    /*---------------------------------------------------------------------- */

    void dispatcher_setup::prompt_packet_limit()
    {
        int64_t input = 0;
        limits_t* old_limits = _limits;

        input = get_console()->prompt(
            0, INT32_MAX, "Enter Packet Limit", "0 = Off");

        if (input > 0)
        {
            _limits = new limits_t(
                old_limits->get_byte_limit(),
                (size_t)input,
                old_limits->get_duration_limit());
        }
        else
        {
            _limits = new limits_t(
                old_limits->get_byte_limit(),
                limits_t::SIZE_UNLIMITED,
                old_limits->get_duration_limit());
        }

        safe_delete(old_limits);

    } /* prompt_packet_limit */

    /*---------------------------------------------------------------------- */

    void dispatcher_setup::prompt_duration_limit()
    {
        int64_t input = 0;
        limits_t* old_limits = _limits;

        input = get_console()->prompt(
            0, INT64_MAX, "Enter Duration Limit (ms)", "0 = Off");

        if (input > 0)
        {
            _limits = new limits_t(
                old_limits->get_byte_limit(),
                old_limits->get_packet_limit(),
                std::chrono::milliseconds{ input });
        }
        else
        {
            _limits = new limits_t(
                old_limits->get_byte_limit(),
                old_limits->get_packet_limit(),
                limits_t::DURATION_UNLIMITED);
        }

        safe_delete(old_limits);

    } /* prompt_duration_limit */

    /*---------------------------------------------------------------------- */

    void dispatcher_setup::prompt_send_delay()
    {
        int64_t input = 0;

        input = get_console()->prompt(
            0, 2, "Enter Delay Type", "0 = Off, 1 = Fixed, 2 = Random");

        switch (input)
        {
            case 0:
                _delay_type = delay_type::NONE;
                break;

            case 1:
                prompt_fixed_send_delay();
                break;

            case 2:
                prompt_random_send_delay();
                break;

            default:
                assert::legal_state(false, "", "Unknown delay type selected");
        }

    } /* prompt_send_delay */

    /*---------------------------------------------------------------------- */

    void dispatcher_setup::prompt_fixed_send_delay()
    {
        int64_t input = 0;

        input = get_console()->prompt(
            0, INT64_MAX, "Enter delay duration (ms)");

        safe_delete(_delay);

        _delay_type = delay_type::FIXED;
        _delay = new fixed_delay_t(
            std::chrono::milliseconds{ input });

    } /* prompt_fixed_send_delay */

    /*---------------------------------------------------------------------- */

    void dispatcher_setup::prompt_random_send_delay()
    {
        int64_t input_a = 0;
        int64_t input_b = 0;
        bool success = false;

        safe_delete(_delay);

        while (!success)
        {
            try
            {
                input_a = get_console()->prompt(
                    0, INT64_MAX, "Enter min delay duration (ms)");

                input_b = get_console()->prompt(
                    0, INT64_MAX, "Enter max delay duration (ms)");

                _delay_type = delay_type::RANDOM;
                _delay = new random_delay_t(
                    std::chrono::milliseconds{ input_a },
                    std::chrono::milliseconds{ input_b });

                success = true;
            }
            catch (const std::out_of_range&)
            {
                get_console()->error_out("Invalid range: Min bigger max");
            }
        }

    } /* prompt_random_send_delay */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
