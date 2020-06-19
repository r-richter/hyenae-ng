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

#include "../../../../include/frontend/console/states/tcp_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    tcp_frame_setup::tcp_frame_setup(
        uint8_t protocol,
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent,
        ip_frame_setup* ip_frame_setup) :
            ip_based_frame_setup(
                context,
                console_io,
                parent,
                ip_frame_setup)
    {
        _protocol = protocol;

        _flags_setup = new tcp_flags_setup(context, console_io, this);

        _menu = new console_menu(
            console_io, get_generator_name() + " Setup");

        _payload = new generator_selector(
            "Payload Setup", context, console_io, this);

        // Default values
        _src_port_pattern = "*****";
        _dst_port_pattern = "*****";
        _seq_num_pattern = "*****";
        _ack_num_pattern = "*****";
        _win_size_pattern = "*****";
        _urg_pointer_pattern = "*****";

        // Source Port
        _src_port_pattern_item = new console_menu::item("Source Port");
        _menu->add_item(_src_port_pattern_item);

        // Destination Port
        _dst_port_pattern_item = new console_menu::item("Destination Port");
        _menu->add_item(_dst_port_pattern_item);

        // Sequence Number
        _seq_num_pattern_item = new console_menu::item("Sequence Number");
        _menu->add_item(_seq_num_pattern_item);

        // Acknowledge Number
        _ack_num_pattern_item = new console_menu::item("Acknowledge Number");
        _menu->add_item(_ack_num_pattern_item);

        // Flags
        _flags_item = new console_menu::item("Flags");
        _menu->add_item(_flags_item);

        // Window Size
        _win_size_pattern_item = new console_menu::item("Window Size");
        _menu->add_item(_win_size_pattern_item);

        // Urgent Pointer
        _urg_pointer_pattern_item = new console_menu::item("Urgent Pointer");
        _menu->add_item(_urg_pointer_pattern_item);

        // Payload
        _payload_item =
            new console_menu::item("Payload");
        _menu->add_item(_payload_item);

        // Back
        _back_item = new console_menu::item("Back");
        _menu->add_item(_back_item);

        update_generator();

    } /* tcp_frame_setup */

    /*---------------------------------------------------------------------- */

    tcp_frame_setup::~tcp_frame_setup()
    {
        safe_delete(_flags_setup);
        safe_delete(_menu);
        safe_delete(_src_port_pattern_item);
        safe_delete(_dst_port_pattern_item);
        safe_delete(_seq_num_pattern_item);
        safe_delete(_ack_num_pattern_item);
        safe_delete(_flags_item);
        safe_delete(_payload_item);
        safe_delete(_win_size_pattern_item);
        safe_delete(_urg_pointer_pattern_item);
        safe_delete(_back_item);
        safe_delete(_generator);
        safe_delete(_payload);

    } /* ~tcp_frame_setup */

    /*---------------------------------------------------------------------- */

    bool tcp_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _src_port_pattern_item)
        {
            prompt_src_port_pattern();
        }
        else if (choice == _dst_port_pattern_item)
        {
            prompt_dst_port_pattern();
        }
        else if (choice == _seq_num_pattern_item)
        {
            prompt_seq_num_pattern();
        }
        else if (choice == _ack_num_pattern_item)
        {
            prompt_ack_num_pattern();
        }
        else if (choice == _flags_item)
        {
            _flags_setup->enter();
        }
        else if (choice == _win_size_pattern_item)
        {
            prompt_win_size_pattern();
        }
        else if (choice == _urg_pointer_pattern_item)
        {
            prompt_urg_pointer_pattern();
        }
        else if (choice == _payload_item)
        {
            _payload->enter();
        }
        else if (choice == _back_item)
        {
            back();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    string_t tcp_frame_setup::get_generator_name() const
    {
        return "TCP-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    tcp_frame_setup::data_generator_t*
        tcp_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void tcp_frame_setup::update_generator()
    {
        update_generator(
            _src_port_pattern,
            _dst_port_pattern,
            _seq_num_pattern,
            _ack_num_pattern,
            _win_size_pattern,
            _urg_pointer_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void tcp_frame_setup::on_select()
    {
        get_ip_frame_setup()->set_protocol(_protocol);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void tcp_frame_setup::update_menu_items()
    {
        _src_port_pattern_item->set_info(_src_port_pattern);
        _dst_port_pattern_item->set_info(_dst_port_pattern);
        _seq_num_pattern_item->set_info(_seq_num_pattern);
        _ack_num_pattern_item->set_info(_ack_num_pattern);
        _flags_item->set_info(_flags_setup->get_flags_info());
        _win_size_pattern_item->set_info(_win_size_pattern);
        _urg_pointer_pattern_item->set_info(_urg_pointer_pattern);
        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void tcp_frame_setup::prompt_src_port_pattern()
    {
        _src_port_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                input,
                _dst_port_pattern,
                _seq_num_pattern,
                _ack_num_pattern,
                _win_size_pattern,
                _urg_pointer_pattern);

            return input;

        },
        "Enter Source Port Pattern",
            _src_port_pattern,
            _src_port_pattern);

    } /* prompt_src_port_pattern */

/*---------------------------------------------------------------------- */

    void tcp_frame_setup::prompt_dst_port_pattern()
    {
        _dst_port_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                _src_port_pattern,
                input,
                _seq_num_pattern,
                _ack_num_pattern,
                _win_size_pattern,
                _urg_pointer_pattern);

            return input;

        },
        "Enter Destination Port Pattern",
            _dst_port_pattern,
            _dst_port_pattern);

    } /* prompt_src_port_pattern */

    /*---------------------------------------------------------------------- */
    void tcp_frame_setup::prompt_seq_num_pattern()
    {
        _seq_num_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                _src_port_pattern,
                _dst_port_pattern,
                input,
                _ack_num_pattern,
                _win_size_pattern,
                _urg_pointer_pattern);

            return input;

        },
        "Enter Sequence Number Pattern",
            _seq_num_pattern,
            _seq_num_pattern);

    } /* prompt_seq_num_pattern */

    void tcp_frame_setup::prompt_ack_num_pattern()
    {
        _ack_num_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                _src_port_pattern,
                _dst_port_pattern,
                _seq_num_pattern,
                input,
                _win_size_pattern,
                _urg_pointer_pattern);

            return input;

        },
        "Enter Acknowledge Number Pattern",
            _ack_num_pattern,
            _ack_num_pattern);

    } /* prompt_ack_num_pattern */

    /*---------------------------------------------------------------------- */

    void tcp_frame_setup::prompt_win_size_pattern()
    {
        _win_size_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                _src_port_pattern,
                _dst_port_pattern,
                _seq_num_pattern,
                _ack_num_pattern,
                input,
                _urg_pointer_pattern);

            return input;

        },
        "Enter Window Size Pattern",
            _win_size_pattern,
            _win_size_pattern);

    } /* prompt_win_size_pattern */

    /*---------------------------------------------------------------------- */

    void tcp_frame_setup::prompt_urg_pointer_pattern()
    {
        _urg_pointer_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                _src_port_pattern,
                _dst_port_pattern,
                _seq_num_pattern,
                _ack_num_pattern,
                _win_size_pattern,
                input);

            return input;

        },
        "Enter Urgent Pointer Pattern",
            _urg_pointer_pattern,
            _urg_pointer_pattern);

    } /* prompt_urg_pointer_pattern */

    /*---------------------------------------------------------------------- */

    void tcp_frame_setup::update_generator(
        string_t src_port_pattern,
        string_t dst_port_pattern,
        string_t seq_num_pattern,
        string_t ack_num_pattern,
        string_t win_size_pattern,
        string_t urg_pointer_pattern)
    {
        safe_delete(_generator);

        _generator = new tcp_frame_generator_t(
            get_ip_frame_setup()->get_pseudo_header(),
            src_port_pattern,
            10,
            dst_port_pattern,
            10,
            seq_num_pattern,
            10,
            ack_num_pattern,
            10,
            _flags_setup->get_cwr_flag(),
            _flags_setup->get_ece_flag(),
            _flags_setup->get_urg_flag(),
            _flags_setup->get_ack_flag(),
            _flags_setup->get_psh_flag(),
            _flags_setup->get_rst_flag(),
            _flags_setup->get_syn_flag(),
            _flags_setup->get_fin_flag(),
            win_size_pattern,
            10,
            urg_pointer_pattern,
            10);

        if (_payload->get_generator() != NULL)
        {
            ((tcp_frame_generator_t*)_generator)->
                get_payload()->add_generator(_payload->get_generator());
        }

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
