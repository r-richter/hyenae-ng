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

        // TODO: Implement...

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

        // TODO: Implement...

        if (choice == _payload_item)
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
        // TODO: Implement...

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
        // TODO: Implement...

        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
