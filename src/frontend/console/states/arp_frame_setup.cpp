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
#include "../../../../include/frontend/console/states/arp_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    arp_frame_setup::arp_frame_setup(
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent,
        ethernet_frame_setup* ethernet_frame_setup) :
        generator_setup(context, console_io, parent)
    {
        assert::argument_not_null(
            _ethernet_frame_setup= ethernet_frame_setup,
            "ethernet_frame_setup");

        _menu = new console_menu(
            console_io, get_generator_name() + " Setup", parent);

        // Default values
        _operation = arp_frame_generator_t::OPERATION_REQUEST;
        _sender_hw_addr_pattern = address_generator_t::RAND_MAC_PATTERN;
        _sender_proto_addr_pattern = address_generator_t::RAND_IP_V4_PATTERN;
        _target_hw_addr_pattern = address_generator_t::RAND_MAC_PATTERN;
        _target_proto_addr_pattern = address_generator_t::RAND_IP_V4_PATTERN;

        // Operation
        _operation_item = new console_menu::item("Operation");
        _menu->add_item(_operation_item);

        // Sender HW-Address
        _sender_hw_addr_pattern_item = new console_menu::item("Sender HW-Address");
        _menu->add_item(_sender_hw_addr_pattern_item);

        // Sender Protocol-Address
        _sender_proto_addr_pattern_item = new console_menu::item(
            "Sender Protocol-Address");
        _menu->add_item(_sender_proto_addr_pattern_item);

        // Target HW-Address
        _target_hw_addr_pattern_item = new console_menu::item("Target HW-Address");
        _menu->add_item(_target_hw_addr_pattern_item);

        // Target Protocol-Address
        _target_proto_addr_pattern_item = new console_menu::item(
            "Target Protocol-Address");
        _menu->add_item(_target_proto_addr_pattern_item);

        update_generator();

    } /* arp_frame_setup */

    /*---------------------------------------------------------------------- */

    arp_frame_setup::~arp_frame_setup()
    {
        safe_delete(_menu);
        safe_delete(_operation_item);
        safe_delete(_sender_hw_addr_pattern_item);
        safe_delete(_sender_proto_addr_pattern_item);
        safe_delete(_target_hw_addr_pattern_item);
        safe_delete(_target_proto_addr_pattern_item);
        safe_delete(_generator);

    } /* ~arp_frame_setup */

    /*---------------------------------------------------------------------- */

    bool arp_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _operation_item)
        {
            prompt_operation();
        }
        else if (choice == _sender_hw_addr_pattern_item)
        {
            prompt_sender_hw_addr_pattern();
        }
        else if (choice == _sender_proto_addr_pattern_item)
        {
            prompt_sender_proto_addr_pattern();
        }
        else if (choice == _target_hw_addr_pattern_item)
        {
            prompt_target_hw_addr_pattern();
        }
        else if (choice == _target_proto_addr_pattern_item)
        {
            prompt_target_proto_addr_pattern();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    string_t arp_frame_setup::get_generator_name() const
    {
        return "ARP-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    arp_frame_setup::data_generator_t*
        arp_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::update_generator()
    {
        update_generator(
            _sender_hw_addr_pattern,
            _sender_proto_addr_pattern,
            _target_hw_addr_pattern,
            _target_proto_addr_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::on_select()
    {
        _ethernet_frame_setup->set_type(
            ethernet_frame_generator_t::TYPE_ARP);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::update_menu_items()
    {

        _operation_item->set_info(std::to_string(_operation));
        _sender_hw_addr_pattern_item->set_info(_sender_hw_addr_pattern);
        _sender_proto_addr_pattern_item->set_info(_sender_proto_addr_pattern);
        _target_hw_addr_pattern_item->set_info(_target_hw_addr_pattern);
        _target_proto_addr_pattern_item->set_info(_target_proto_addr_pattern);

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::prompt_operation()
    {
        _operation = (uint16_t) get_console()->prompt(
            1, 2, "Enter Operation", "1 = Request, 2 = Reply");

    } /* prompt_operation */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::prompt_sender_hw_addr_pattern()
    {
        _sender_hw_addr_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                input,
                _sender_proto_addr_pattern,
                _target_hw_addr_pattern,
                _target_proto_addr_pattern);

            return input;

        },
        "Enter Sender HW-Address Pattern",
            _sender_hw_addr_pattern,
            _sender_hw_addr_pattern);

    } /* prompt_sender_hw_addr_pattern */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::prompt_sender_proto_addr_pattern()
    {
        _sender_proto_addr_pattern =
            get_console()->prompt([this](string_t input)
        {
            update_generator(
                _sender_hw_addr_pattern,
                input,
                _target_hw_addr_pattern,
                _target_proto_addr_pattern);

            return input;

        },
        "Enter Sender Protocol-Address Pattern",
            _sender_proto_addr_pattern,
            _sender_proto_addr_pattern);

    } /* prompt_sender_proto_addr_pattern */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::prompt_target_hw_addr_pattern()
    {
        _target_hw_addr_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                _sender_hw_addr_pattern,
                _target_proto_addr_pattern,
                input,
                _target_proto_addr_pattern);

            return input;

        },
        "Enter Target HW-Address Pattern",
            _target_hw_addr_pattern,
            _target_hw_addr_pattern);

    } /* prompt_target_hw_addr_pattern */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::prompt_target_proto_addr_pattern()
    {
        _target_proto_addr_pattern =
            get_console()->prompt([this](string_t input)
        {
            update_generator(
                _target_hw_addr_pattern,
                _target_proto_addr_pattern,
                _target_hw_addr_pattern,
                input);

            return input;
            
        },
        "Enter Target Protocol-Address Pattern",
            _target_proto_addr_pattern,
            _target_proto_addr_pattern);

    } /* prompt_target_proto_addr_pattern */

    /*---------------------------------------------------------------------- */

    void arp_frame_setup::update_generator(
        string_t sender_hw_addr_pattern,
        string_t sender_proto_addr_pattern,
        string_t target_hw_addr_pattern,
        string_t target_proto_addr_pattern)
    {
        safe_delete(_generator);

        _generator = arp_frame_generator_t::create_for_ip_v4_over_ethernet(
            _operation,
            sender_hw_addr_pattern,
            sender_proto_addr_pattern,
            target_hw_addr_pattern,
            target_proto_addr_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
