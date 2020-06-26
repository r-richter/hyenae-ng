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

#include "../../../../include/frontend/console/states/dhcp_v4_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    dhcp_v4_frame_setup::dhcp_v4_frame_setup(
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
        _opcode = dhcp_v4_frame_generator_t::OPCODE_REQUEST;
        _hops = 1;
        _xid_pattern = "****";
        _seconds_pattern = "****";
        _broadcast_flag = false;
        _client_ip_pattern = address_generator_t::RAND_IP_V4_PATTERN;
        _your_ip_pattern = address_generator_t::RAND_IP_V4_PATTERN;
        _server_ip_pattern = address_generator_t::RAND_IP_V4_PATTERN;
        _gateway_ip_pattern = address_generator_t::RAND_IP_V4_PATTERN;
        _client_mac_pattern = address_generator_t::RAND_MAC_PATTERN;
        _server_name = "";
        _file = "";

        // Opcode
        _opcode_item = new console_menu::item("Opcode");
        _menu->add_item(_opcode_item);

        // Hops
        _hops_item = new console_menu::item("Hops");
        _menu->add_item(_hops_item);

        // XID
        _xid_item = new console_menu::item("XID");
        _menu->add_item(_xid_item);

        // Seconds
        _seconds_item = new console_menu::item("Seconds");
        _menu->add_item(_seconds_item);

        // Broadcast Flag
        _broadcast_flag_item = new console_menu::item("Broadcast Flag");
        _menu->add_item(_broadcast_flag_item);

        // Client IP-Address
        _client_ip_addr_item = new console_menu::item("Client IP-Address");
        _menu->add_item(_client_ip_addr_item);

        // Your IP-Address
        _your_ip_addr_item = new console_menu::item("Your IP-Address");
        _menu->add_item(_your_ip_addr_item);

        // Server IP-Address
        _server_ip_addr_item = new console_menu::item("Server IP-Address");
        _menu->add_item(_server_ip_addr_item);

        // Gateway IP-Address
        _gateway_ip_addr_item = new console_menu::item("Gateway IP-Address");
        _menu->add_item(_gateway_ip_addr_item);

        // Client MAC-Address
        _client_mac_addr_item = new console_menu::item("Client MAC-Address");
        _menu->add_item(_client_mac_addr_item);

        // Server Name
        _server_name_item = new console_menu::item("Server Name");
        _menu->add_item(_server_name_item);

        // File
        _file_item = new console_menu::item("File");
        _menu->add_item(_file_item);
        
        // Payload
        _payload_item =
            new console_menu::item("Payload");
        _menu->add_item(_payload_item);

        update_generator();

    } /* dhcp_v4_frame_setup */

    /*---------------------------------------------------------------------- */

    dhcp_v4_frame_setup::~dhcp_v4_frame_setup()
    {
        safe_delete(_menu);
        safe_delete(_opcode_item);
        safe_delete(_hops_item);
        safe_delete(_xid_item);
        safe_delete(_seconds_item);
        safe_delete(_broadcast_flag_item);
        safe_delete(_client_ip_addr_item);
        safe_delete(_your_ip_addr_item);
        safe_delete(_server_ip_addr_item);
        safe_delete(_gateway_ip_addr_item);
        safe_delete(_client_mac_addr_item);
        safe_delete(_server_name_item);
        safe_delete(_file_item);
        safe_delete(_payload_item);
        safe_delete(_generator);
        safe_delete(_payload);

    } /* ~dhcp_v4_frame_setup */

    /*---------------------------------------------------------------------- */

    bool dhcp_v4_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        _menu->set_start_state(get_start_state());
        _payload->set_start_state(get_start_state());

        console_menu::item* choice = _menu->prompt();

        if (choice == _opcode_item)
        {
            prompt_opcode();
        }
        else if (choice == _hops_item)
        {
            prompt_hops();
        }
        else if (choice == _xid_item)
        {
            prompt_xid();
        }
        else if (choice == _seconds_item)
        {
            prompt_seconds();
        }
        else if (choice == _broadcast_flag_item)
        {
            prompt_broadcast_flag();
        }
        else if (choice == _client_ip_addr_item)
        {
            prompt_client_ip_addr();
        }
        else if (choice == _your_ip_addr_item)
        {
            prompt_your_ip_addr();
        }
        else if (choice == _server_ip_addr_item)
        {
            prompt_server_ip_addr();
        }
        else if (choice == _gateway_ip_addr_item)
        {
            prompt_gateway_ip_addr();
        }
        else if (choice == _client_mac_addr_item)
        {
            prompt_client_mac_addr();
        }
        else if (choice == _server_name_item)
        {
            prompt_server_name();
        }
        else if (choice == _file_item)
        {
            prompt_file();
        }
        else if (choice == _payload_item)
        {
            _payload->enter();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    string_t dhcp_v4_frame_setup::get_generator_name() const
    {
        return "DHCPv4-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    dhcp_v4_frame_setup::data_generator_t*
        dhcp_v4_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::update_generator()
    {
        update_generator(
            _xid_pattern,
            _seconds_pattern,
            _client_ip_pattern,
            _your_ip_pattern,
            _server_ip_pattern,
            _gateway_ip_pattern,
            _client_mac_pattern
        );

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::on_select()
    {
        get_udp_frame_setup()->set_src_port(
            dhcp_v4_frame_generator_t::CLIENT_PORT);

        get_udp_frame_setup()->set_dst_port(
            dhcp_v4_frame_generator_t::SERVER_PORT);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::update_menu_items()
    {
        // TODO: Display opcode mode name instead of number
        _opcode_item->set_info(std::to_string(_opcode));
        _hops_item->set_info(std::to_string(_hops));
        _xid_item->set_info(_xid_pattern);
        _seconds_item->set_info(_seconds_pattern);
        _broadcast_flag_item->set_info(_broadcast_flag ? "On" : "Off");
        _client_ip_addr_item->set_info(_client_ip_pattern);
        _your_ip_addr_item->set_info(_your_ip_pattern);
        _server_ip_addr_item->set_info(_server_ip_pattern);
        _gateway_ip_addr_item->set_info(_gateway_ip_pattern);
        _client_mac_addr_item->set_info(_client_mac_pattern);
        _server_name_item->set_info(_server_name);
        _file_item->set_info(_file);
        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_opcode()
    {
        _opcode = (uint16_t) get_console()->prompt(
            1, 2, "Enter Opcode", "1 = Request, 2 = Reply");

    } /* prompt_opcode */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_hops()
    {
        _hops = (uint8_t)get_console()->prompt(
            0, UINT8_MAX, "Enter Hops (Decimal)");

    } /* prompt_hops */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_xid()
    {
        _xid_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    input,
                    _seconds_pattern,
                    _client_ip_pattern,
                    _your_ip_pattern,
                    _server_ip_pattern,
                    _gateway_ip_pattern,
                    _client_mac_pattern);

                return input;

            },
            "Enter XID Pattern",
                _xid_pattern,
                _xid_pattern);

    } /* prompt_xid */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_seconds()
    {
        _seconds_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _xid_pattern,
                    input,
                    _client_ip_pattern,
                    _your_ip_pattern,
                    _server_ip_pattern,
                    _gateway_ip_pattern,
                    _client_mac_pattern);

                return input;

            },
            "Enter Seconds Pattern",
                _seconds_pattern,
                _seconds_pattern);

    } /* prompt_seconds */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_broadcast_flag()
    {
        _broadcast_flag = get_console()->prompt(
            0, 1, "Broadcast Flag", "0 = Off, 1 = On");

    } /* prompt_broadcast_flag */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_client_ip_addr()
    {
        _client_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _xid_pattern,
                    _seconds_pattern,
                    input,
                    _your_ip_pattern,
                    _server_ip_pattern,
                    _gateway_ip_pattern,
                    _client_mac_pattern);

                return input;

            },
            "Enter Client IP-Address Pattern",
                _client_ip_pattern,
                _client_ip_pattern);

    } /* prompt_client_ip_addr */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_your_ip_addr()
    {
        _your_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _xid_pattern,
                    _seconds_pattern,
                    _client_ip_pattern,
                    input,
                    _server_ip_pattern,
                    _gateway_ip_pattern,
                    _client_mac_pattern);

                return input;

            },
            "Enter Your IP-Address Pattern",
                _your_ip_pattern,
                _your_ip_pattern);

    } /* prompt_your_ip_addr */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_server_ip_addr()
    {
       _server_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _xid_pattern,
                    _seconds_pattern,
                    _client_ip_pattern,
                    _your_ip_pattern,
                    input,
                    _gateway_ip_pattern,
                    _client_mac_pattern);

                return input;

            },
            "Enter Server IP-Address Pattern",
                _server_ip_pattern,
                _server_ip_pattern);

    } /* prompt_server_ip_addr */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_gateway_ip_addr()
    {
        _gateway_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _xid_pattern,
                    _seconds_pattern,
                    _client_ip_pattern,
                    _your_ip_pattern,
                    _server_ip_pattern,
                    input,
                    _client_mac_pattern);

                return input;

            },
            "Enter Gateway IP-Address Pattern",
                _gateway_ip_pattern,
                _gateway_ip_pattern);

    } /* prompt_gateway_ip_addr */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_client_mac_addr()
    {
        _client_mac_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _xid_pattern,
                    _seconds_pattern,
                    _client_ip_pattern,
                    _your_ip_pattern,
                    _server_ip_pattern,
                    _gateway_ip_pattern,
                    input);

                return input;

            },
            "Enter Client MAC-Address Pattern",
                _client_mac_pattern,
                _client_mac_pattern);

    } /* prompt_client_mac_addr */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_server_name()
    {
        _server_name = get_console()->prompt("Enter Server Name");

    } /* prompt_server_name */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::prompt_file()
    {
        _file = get_console()->prompt("Enter File");

    } /* prompt_file */

    /*---------------------------------------------------------------------- */

    void dhcp_v4_frame_setup::update_generator(
        string_t xid_pattern,
        string_t seconds_pattern,
        string_t client_ip_pattern,
        string_t your_ip_pattern,
        string_t server_ip_pattern,
        string_t gateway_ip_pattern,
        string_t client_mac_pattern)
    {
        safe_delete(_generator);

        _generator = dhcp_v4_frame_generator_t::create_for_ethernet(
            _opcode,
            _hops,
            xid_pattern,
            10,
            seconds_pattern,
            10,
            _broadcast_flag,
            client_ip_pattern,
            your_ip_pattern,
            server_ip_pattern,
            gateway_ip_pattern,
            client_mac_pattern,
            _server_name,
            _file);

        // Update payload in order to have it's
        // pseudo header re-assigned.
        _payload->update_generator();

        if (_payload->get_generator() != NULL)
        {
            ((dhcp_v4_frame_generator_t*)_generator)->
                get_payload()->add_generator(_payload->get_generator());
        }
    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
