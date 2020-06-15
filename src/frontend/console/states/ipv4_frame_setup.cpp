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

#include "../../../../include/frontend/console/states/ipv4_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    ipv4_frame_setup::ipv4_frame_setup(
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent,
        ethernet_frame_setup* ethernet_frame_setup) :
            ip_frame_setup(context, console_io, parent, ethernet_frame_setup)
    {
        _menu = new console_menu(
            console_io, get_generator_name() + " Setup");

        _payload = new generator_selector(
            "Payload Setup", context, console_io, this);

        // Default values
        _type_of_service = 0;
        _id_pattern = "*****";
        _dont_frag = false;
        _more_frags = false;
        _frag_offset_pattern = "0";
        _time_to_live = 128;
        _protocol = 0;
        _src_ip_pattern = address_generator_t::RAND_IP_V4_PATTERN;
        _dst_ip_pattern = address_generator_t::RAND_IP_V4_PATTERN;

        // Type Of Service
        _type_of_service_item = new console_menu::item("Type Of Service");
        _menu->add_item(_type_of_service_item);

        // ID-Pattern
        _id_pattern_item = new console_menu::item("Identification");
        _menu->add_item(_id_pattern_item);

        // Don't Fragment
        _dont_frag_item = new console_menu::item("Don't Fragment");
        _menu->add_item(_dont_frag_item);

        // More Fragments
        _more_frags_item = new console_menu::item("More Fragments");
        _menu->add_item(_more_frags_item);

        // Fragment-Offset
        _frag_offset_item = new console_menu::item("Fragment-Offset");
        _menu->add_item(_frag_offset_item);

        // Time To Live
        _time_to_live_item = new console_menu::item("Time To Live");
        _menu->add_item(_time_to_live_item);

        // Protocol
        _protocol_item = new console_menu::item("Protocol");
        _menu->add_item(_protocol_item);

        // Source-Address
        _src_ip_pattern_item = new console_menu::item("Source-Address");
        _menu->add_item(_src_ip_pattern_item);

        // Destination-Address
        _dst_ip_pattern_item = new console_menu::item("Destination-Address");
        _menu->add_item(_dst_ip_pattern_item);

        // Payload
        _payload_item =
            new console_menu::item("Payload");
        _menu->add_item(_payload_item);

        // Back
        _back_item = new console_menu::item("Back");
        _menu->add_item(_back_item);

        update_generator();

    } /* ipv4_frame_setup */

    /*---------------------------------------------------------------------- */

    ipv4_frame_setup::~ipv4_frame_setup()
    {
        safe_delete(_menu);
        safe_delete(_type_of_service_item);
        safe_delete(_id_pattern_item);
        safe_delete(_dont_frag_item);
        safe_delete(_more_frags_item);
        safe_delete(_frag_offset_item);
        safe_delete(_time_to_live_item);
        safe_delete(_protocol_item);
        safe_delete(_src_ip_pattern_item);
        safe_delete(_dst_ip_pattern_item);
        safe_delete(_payload_item);
        safe_delete(_back_item);
        safe_delete(_generator);
        safe_delete(_payload);

    } /* ~ipv4_frame_setup */

    /*---------------------------------------------------------------------- */

    bool ipv4_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _type_of_service_item)
        {
            prompt_type_of_service();
        }
        else if (choice == _id_pattern_item)
        {
            prompt_id_pattern();
        }
        else if (choice == _dont_frag_item)
        {
            prompt_dont_frag();
        }
        else if (choice == _more_frags_item)
        {
            prompt_more_frags();
        }
        else if (choice == _frag_offset_item)
        {
            prompt_frag_offset();
        }
        else if (choice == _time_to_live_item)
        {
            prompt_time_to_live();
        }
        else if (choice == _protocol_item)
        {
            prompt_protocol();
        }
        else if (choice == _src_ip_pattern_item)
        {
            prompt_src_ip_pattern();
        }
        else if (choice == _dst_ip_pattern_item)
        {
            prompt_dst_ip_pattern();
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

    uint8_t ipv4_frame_setup::get_protocol() const
    {
        return _protocol;

    } /* get_protocol */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::set_protocol(uint8_t protocol)
    {
        _protocol = protocol;

    } /* set_protocol */

    /*---------------------------------------------------------------------- */

    string_t ipv4_frame_setup::get_generator_name() const
    {
        return "IPv4-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    ipv4_frame_setup::data_generator_t*
        ipv4_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    ipv4_frame_setup::data_generator_t*
        ipv4_frame_setup::get_pseudo_header() const
    {
        return ((ipv4_frame_generator_t*)_generator)->get_pseudo_header();

    } /* get_pseudo_header */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::update_generator()
    {
        update_generator(
            _id_pattern,
            _frag_offset_pattern,
            _src_ip_pattern,
            _dst_ip_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::on_select()
    {
        get_ethernet_frame_setup()->set_type(
            ethernet_frame_generator_t::TYPE_IPV4);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::update_menu_items()
    {
        _type_of_service_item->set_info(std::to_string(_type_of_service));
        _id_pattern_item->set_info(_id_pattern);
        _dont_frag_item->set_info(_dont_frag ? "On" : "Off");
        _more_frags_item->set_info(_more_frags ? "On" : "Off");
        _frag_offset_item->set_info(concat(_frag_offset_pattern, " (x 8)"));
        _time_to_live_item->set_info(std::to_string(_time_to_live));
        _protocol_item->set_info(std::to_string(_protocol));
        _src_ip_pattern_item->set_info(_src_ip_pattern);
        _dst_ip_pattern_item->set_info(_dst_ip_pattern);
        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_type_of_service()
    {
        _type_of_service = (uint8_t)get_console()->prompt(
            0, INT64_MAX, "Enter Type Of Service (Decimal)");

    } /* prompt_type_of_service */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_id_pattern()
    {
        _id_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                input,
                _frag_offset_pattern,
                _src_ip_pattern,
                _dst_ip_pattern);

            return input;

        },
        "Enter Identification Pattern",
            _id_pattern,
            _id_pattern);

    } /* prompt_id_pattern */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_dont_frag()
    {
        _dont_frag = get_console()->prompt(
            0, 1, "Don't Fragment", "0 = Off, 1 = On");

    } /* prompt_dont_frag */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_more_frags()
    {
        _more_frags = get_console()->prompt(
            0, 1, "More Fragments", "0 = Off, 1 = On");

    } /* prompt_more_frags */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_frag_offset()
    {
        _frag_offset_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _id_pattern,
                    input,
                    _src_ip_pattern,
                    _dst_ip_pattern);

                return input;

            },
            "Enter Fragment-Offset Pattern (1 Unit = 8 Bytes)",
                _frag_offset_pattern,
                _frag_offset_pattern);

    } /* prompt_frag_offset */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_time_to_live()
    {
        _time_to_live = (uint8_t)get_console()->prompt(
            0, 255, "Enter Time To Live (Decimal)", "0-255");

    } /* prompt_time_to_live */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_protocol()
    {
        _protocol = (uint8_t)get_console()->prompt(
            0, 255, "Enter Protocol (Decimal)", "0-255");

    } /* prompt_protocol */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_src_ip_pattern()
    {
        _src_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _id_pattern,
                    _frag_offset_pattern,
                    input,
                    _dst_ip_pattern);

                return input;

            },
            "Enter Source-Address Pattern",
                _src_ip_pattern,
                _src_ip_pattern);

    } /* prompt_src_ip_pattern */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::prompt_dst_ip_pattern()
    {
        _dst_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _id_pattern,
                    _frag_offset_pattern,
                    _src_ip_pattern,
                    input);

                return input;

            },
            "Enter Destination-Address Pattern",
                _dst_ip_pattern,
                _dst_ip_pattern);

    } /* prompt_dst_ip_pattern */

    /*---------------------------------------------------------------------- */

    void ipv4_frame_setup::update_generator(
        string_t id_pattern,
        string_t _frag_offset,
        string_t src_ip_pattern,
        string_t dst_ip_pattern)
    {
        safe_delete(_generator);

        _generator = new ipv4_frame_generator_t(
            _type_of_service,
            id_pattern,
            10,
            _dont_frag,
            _more_frags,
            _frag_offset,
            10,
            _time_to_live,
            _protocol,
            src_ip_pattern,
            dst_ip_pattern);

        // Update payload in order to have it's
        // pseudo header re-assigned.
        _payload->update_generator();

        if (_payload->get_generator() != NULL)
        {
            ((ipv4_frame_generator_t*)_generator)->
                get_payload()->add_generator(_payload->get_generator());
        }

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
