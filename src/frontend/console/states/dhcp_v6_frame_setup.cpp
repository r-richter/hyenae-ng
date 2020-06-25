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

#include "../../../../include/frontend/console/states/dhcp_v6_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    dhcp_v6_frame_setup::dhcp_v6_frame_setup(
        console_app_state_context* context,
        console_app_config* config,
        console_io* console_io,
        console_app_state* parent,
        udp_frame_setup* udp_frame_setup) :
            udp_based_frame_setup(
                context,
                config,
                console_io,
                parent,
                udp_frame_setup)
    {
        _menu = new console_menu(
            console_io, get_generator_name() + " Setup", this, parent);

        _payload = new generator_selector(
            "Payload Setup", context, config, console_io, this);

        // Default values
        _msg_type = 0;
        _transaction_id_pattern = "*****";

        // Message Type
        _msg_type_item = new console_menu::item("Message Type");
        _menu->add_item(_msg_type_item);

        // Transaction ID
        _transaction_id_pattern_item =
            new console_menu::item("Transaction ID");
        _menu->add_item(_transaction_id_pattern_item);

        // Payload
        _payload_item =
            new console_menu::item("Payload");
        _menu->add_item(_payload_item);

        update_generator();

    } /* dhcp_v6_frame_setup */

    /*---------------------------------------------------------------------- */

    dhcp_v6_frame_setup::~dhcp_v6_frame_setup()
    {
        safe_delete(_menu);
        safe_delete(_msg_type_item);
        safe_delete(_msg_type_item);
        safe_delete(_payload_item);
        safe_delete(_generator);
        safe_delete(_payload);

    } /* ~dhcp_v6_frame_setup */

    /*---------------------------------------------------------------------- */

    bool dhcp_v6_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        _menu->set_start_state(get_start_state());
        _payload->set_start_state(get_start_state());

        console_menu::item* choice = _menu->prompt();

        if (choice == _msg_type_item)
        {
            prompt_msg_type_item();
        }
        else if (choice == _transaction_id_pattern_item)
        {
            prompt_transaction_id_pattern_item();
        }
        else if (choice == _payload_item)
        {
            _payload->enter();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    string_t dhcp_v6_frame_setup::get_generator_name() const
    {
        return "DHCPv6-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    dhcp_v6_frame_setup::data_generator_t*
        dhcp_v6_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void dhcp_v6_frame_setup::update_generator()
    {
        update_generator(_transaction_id_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void dhcp_v6_frame_setup::on_select()
    {
        get_udp_frame_setup()->set_src_port(
            dhcp_v6_frame_generator_t::CLIENT_PORT);

        get_udp_frame_setup()->set_dst_port(
            dhcp_v6_frame_generator_t::SERVER_PORT);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void dhcp_v6_frame_setup::update_menu_items()
    {
        _msg_type_item->set_info(std::to_string(_msg_type));
        _transaction_id_pattern_item->set_info(_transaction_id_pattern);
        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void dhcp_v6_frame_setup::prompt_msg_type_item()
    {
        _msg_type = (uint8_t)get_console()->prompt(
            0, UINT8_MAX, "Enter Message Type (Decimal)");

    } /* prompt_msg_type_item */

/*---------------------------------------------------------------------- */

    void dhcp_v6_frame_setup::prompt_transaction_id_pattern_item()
    {
        _transaction_id_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(input);

                return input;

            },
            "Enter Transaction Id Pattern",
                _transaction_id_pattern,
                _transaction_id_pattern);

    } /* prompt_transaction_id_pattern_item */

    /*---------------------------------------------------------------------- */

    void dhcp_v6_frame_setup::update_generator(
        string_t transaction_id_pattern)
    {
        safe_delete(_generator);
        
        _generator = new dhcp_v6_frame_generator_t(
            _msg_type,
            transaction_id_pattern,
            10);

        _payload->update_generator();

        if (_payload->get_generator() != NULL)
        {
            ((dhcp_v6_frame_generator_t*)_generator)->
                get_payload()->add_generator(_payload->get_generator());
        }

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
