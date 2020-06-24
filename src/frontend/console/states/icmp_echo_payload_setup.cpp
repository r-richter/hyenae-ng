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

#include "../../../../include/frontend/console/states/icmp_echo_payload_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    icmp_echo_payload_setup::icmp_echo_payload_setup(
        uint8_t type,
        uint8_t code,
        console_app_state_context* context,
        console_app_config* config,
        console_io* console_io,
        console_app_state* parent,
        icmp_frame_setup* icmp_frame_setup) :
            generator_setup(context, config, console_io, parent)
    {
        assert::argument_not_null(
            _icmp_frame_setup = icmp_frame_setup, "icmp_frame_setup");

        _type = type;
        _code = code;

        _menu = new console_menu(
            console_io, get_generator_name() + " Setup", this, parent);

        // Default values
        _id_pattern = "*****";
        _seq_num_pattern = "*****";

        // Identification
        _id_pattern_item = new console_menu::item("Identification");
        _menu->add_item(_id_pattern_item);

        // Sequence Number
        _seq_num_pattern_item = new console_menu::item("Sequence Number");
        _menu->add_item(_seq_num_pattern_item);

        update_generator();

    } /* icmp_echo_payload_setup */

    /*---------------------------------------------------------------------- */

    icmp_echo_payload_setup::~icmp_echo_payload_setup()
    {
        safe_delete(_menu);
        safe_delete(_id_pattern_item);
        safe_delete(_seq_num_pattern_item);
        safe_delete(_generator);

    } /* ~icmp_echo_payload_setup */

    /*---------------------------------------------------------------------- */

    bool icmp_echo_payload_setup::run()
    {
        update_generator();
        update_menu_items();

        _menu->set_start_state(get_start_state());

        console_menu::item* choice = _menu->prompt();

        if (choice == _id_pattern_item)
        {
            prompt_id_pattern();
        }
        else if (choice == _seq_num_pattern_item)
        {
            prompt_seq_num_pattern();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    string_t icmp_echo_payload_setup::get_generator_name() const
    {
        return "ICMP Echo Payload";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    icmp_echo_payload_setup::data_generator_t*
        icmp_echo_payload_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void icmp_echo_payload_setup::update_generator()
    {
        update_generator(
            _id_pattern,
            _seq_num_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void icmp_echo_payload_setup::on_select()
    {
        _icmp_frame_setup->set_type(_type);
        _icmp_frame_setup->set_code(_code);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void icmp_echo_payload_setup::update_menu_items()
    {
        _id_pattern_item->set_info(_id_pattern);
        _seq_num_pattern_item->set_info(_seq_num_pattern);

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void icmp_echo_payload_setup::prompt_id_pattern()
    {
        _id_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                input,
                _seq_num_pattern);

            return input;

        },
        "Enter Identification Pattern",
            _id_pattern,
            _id_pattern);

    } /* prompt_id_pattern */

/*---------------------------------------------------------------------- */

    void icmp_echo_payload_setup::prompt_seq_num_pattern()
    {
        _seq_num_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                _id_pattern,
                input);

            return input;

        },
        "Enter Sequence Number Pattern",
            _seq_num_pattern,
            _seq_num_pattern);

    } /* prompt_seq_num_pattern */

    /*---------------------------------------------------------------------- */

    void icmp_echo_payload_setup::update_generator(
        string_t id_pattern,
        string_t seq_num_pattern)
    {
        safe_delete(_generator);
        
        _generator = new icmp_echo_payload_generator_t(
            id_pattern,
            10,
            seq_num_pattern,
            10);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
