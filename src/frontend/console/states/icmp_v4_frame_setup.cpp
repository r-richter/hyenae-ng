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

#include "../../../../include/frontend/console/states/icmp_v4_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    icmp_v4_frame_setup::icmp_v4_frame_setup(
        uint8_t protocol,
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent,
        ip_frame_setup* ip_frame_setup) :
            icmp_frame_setup(
                context,
                console_io,
                parent,
                ip_frame_setup)
    {
        _protocol = protocol;

        _menu = new console_menu(
            console_io, get_generator_name() + " Setup");

        _payload = new generator_selector(
            "Payload Setup", context, console_io, this);

        // Default values
        _type = 0;
        _code = 0;

        // Type
        _type_item = new console_menu::item("Type");
        _menu->add_item(_type_item);

        // Code
        _code_item = new console_menu::item("Code");
        _menu->add_item(_code_item);

        // Payload
        _payload_item =
            new console_menu::item("Payload");
        _menu->add_item(_payload_item);

        // Back
        _back_item = new console_menu::item("Back");
        _menu->add_item(_back_item);

        update_generator();

    } /* icmp_v4_frame_setup */

    /*---------------------------------------------------------------------- */

    icmp_v4_frame_setup::~icmp_v4_frame_setup()
    {
        safe_delete(_menu);
        safe_delete(_type_item);
        safe_delete(_code_item);
        safe_delete(_payload_item);
        safe_delete(_back_item);
        safe_delete(_generator);
        safe_delete(_payload);

    } /* ~icmp_v4_frame_setup */

    /*---------------------------------------------------------------------- */

    bool icmp_v4_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _type_item)
        {
            prompt_type();
        }
        else if (choice == _code_item)
        {
            prompt_code();
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

    string_t icmp_v4_frame_setup::get_generator_name() const
    {
        return "ICMPv4-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    icmp_v4_frame_setup::data_generator_t*
        icmp_v4_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    uint8_t icmp_v4_frame_setup::get_type() const
    {
        return _type;

    } /* get_type */

    /*---------------------------------------------------------------------- */

    void icmp_v4_frame_setup::set_type(uint8_t type)
    {
        _type = type;

    } /* set_type */

    /*---------------------------------------------------------------------- */

    uint8_t icmp_v4_frame_setup::get_code() const
    {
        return _code;

    } /* get_code */

    /*---------------------------------------------------------------------- */

    void icmp_v4_frame_setup::set_code(uint8_t code)
    {
        _code = code;

    } /* set_code */

    /*---------------------------------------------------------------------- */

    void icmp_v4_frame_setup::update_generator()
    {
        safe_delete(_generator);

        _generator = new icmp_v4_frame_generator_t(
            _type,
            _code);

        if (_payload->get_generator() != NULL)
        {
            ((icmp_v4_frame_generator_t*)_generator)->
                get_payload()->add_generator(_payload->get_generator());
        }

    } /* update_generator */

   /*---------------------------------------------------------------------- */

    void icmp_v4_frame_setup::on_select()
    {
        get_ip_frame_setup()->set_protocol(_protocol);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void icmp_v4_frame_setup::update_menu_items()
    {
        _type_item->set_info(std::to_string(_type));
        _code_item->set_info(std::to_string(_code));
        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void icmp_v4_frame_setup::prompt_type()
    {
        _type = (uint8_t)get_console()->prompt(
            0, UINT8_MAX, "Enter Type (Decimal)");

    } /* prompt_type */

/*---------------------------------------------------------------------- */

    void icmp_v4_frame_setup::prompt_code()
    {
        _code = (uint8_t)get_console()->prompt(
            0, UINT8_MAX, "Enter Code (Decimal)");

    } /* prompt_code */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
