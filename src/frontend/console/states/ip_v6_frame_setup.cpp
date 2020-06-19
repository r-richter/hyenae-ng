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

#include "../../../../include/frontend/console/states/ip_v6_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    ip_v6_frame_setup::ip_v6_frame_setup(
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
        _traffic_class = 0;
        _flow_label_pattern = "*****";
        _next_header = 0;
        _hop_limit = 128;
        _src_ip_pattern = address_generator_t::RAND_IP_V6_PATTERN;
        _dst_ip_pattern = address_generator_t::RAND_IP_V6_PATTERN;

        // Traffic Class
        _traffic_class_item = new console_menu::item("Traffic Class");
        _menu->add_item(_traffic_class_item);

        // FLow-Label Pattern
        _flow_label_pattern_item = new console_menu::item("Flow Label");
        _menu->add_item(_flow_label_pattern_item);

        // Next Header
        _next_header_item = new console_menu::item("Next Header");
        _menu->add_item(_next_header_item);

        // Hop Limit
        _hop_limit_item = new console_menu::item("Hop Limit");
        _menu->add_item(_hop_limit_item);

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

        update_generator();

    } /* ip_v6_frame_setup */

    /*---------------------------------------------------------------------- */

    ip_v6_frame_setup::~ip_v6_frame_setup()
    {
        safe_delete(_menu);
        safe_delete(_traffic_class_item);
        safe_delete(_flow_label_pattern_item);
        safe_delete(_next_header_item);
        safe_delete(_hop_limit_item);
        safe_delete(_src_ip_pattern_item);
        safe_delete(_dst_ip_pattern_item);
        safe_delete(_payload_item);
        safe_delete(_generator);
        safe_delete(_payload);

    } /* ~ip_v6_frame_setup */

    /*---------------------------------------------------------------------- */

    bool ip_v6_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _traffic_class_item)
        {
            prompt_traffic_class();
        }
        else if (choice == _flow_label_pattern_item)
        {
            prompt_flow_label_pattern();
        }
        else if (choice == _next_header_item)
        {
            prompt_next_header();
        }
        else if (choice == _hop_limit_item)
        {
            prompt_hop_limit();
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
        else if (choice == _menu->get_back_item())
        {
            back();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    uint8_t ip_v6_frame_setup::get_protocol() const
    {
        return _next_header;

    } /* get_protocol */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::set_protocol(uint8_t protocol)
    {
        _next_header = protocol;

    } /* set_protocol */

    /*---------------------------------------------------------------------- */

    string_t ip_v6_frame_setup::get_generator_name() const
    {
        return "IPv6-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    ip_v6_frame_setup::data_generator_t*
        ip_v6_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    ip_v6_frame_setup::data_generator_t*
        ip_v6_frame_setup::get_pseudo_header() const
    {
        return ((ip_v6_frame_generator_t*)_generator)->get_pseudo_header();

    } /* get_pseudo_header */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::update_generator()
    {
        update_generator(
            _flow_label_pattern,
            _src_ip_pattern,
            _dst_ip_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::on_select()
    {
        get_ethernet_frame_setup()->set_type(
            ethernet_frame_generator_t::TYPE_IP_V6);

    } /* on_select */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::update_menu_items()
    {
        _traffic_class_item->set_info(std::to_string(_traffic_class));
        _flow_label_pattern_item->set_info(_flow_label_pattern);
        _next_header_item->set_info(std::to_string(_next_header));
        _hop_limit_item->set_info(std::to_string(_hop_limit));
        _src_ip_pattern_item->set_info(_src_ip_pattern);
        _dst_ip_pattern_item->set_info(_dst_ip_pattern);
        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::prompt_traffic_class()
    {
        _traffic_class = (uint8_t)get_console()->prompt(
            0, UINT8_MAX, "Enter Traffic Class (Decimal)");

    } /* prompt_traffic_class */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::prompt_flow_label_pattern()
    {
        _flow_label_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(
                input,
                _src_ip_pattern,
                _dst_ip_pattern);

            return input;

        },
        "Enter Flow-Label Pattern",
            _flow_label_pattern,
            _flow_label_pattern);

    } /* prompt_flow_label_pattern */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::prompt_next_header()
    {
        _next_header = (uint8_t)get_console()->prompt(
            0, UINT8_MAX, "Enter Next Header (Decimal)", "0-255");

    } /* prompt_next_header */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::prompt_hop_limit()
    {
        _hop_limit = (uint8_t)get_console()->prompt(
            0, UINT8_MAX, "Enter Hop Limit (Decimal)", "0-255");

    } /* prompt_hop_limit */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::prompt_src_ip_pattern()
    {
        _src_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _flow_label_pattern,
                    input,
                    _dst_ip_pattern);

                return input;

            },
            "Enter Source-Address Pattern",
                _src_ip_pattern,
                _src_ip_pattern);

    } /* prompt_src_ip_pattern */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::prompt_dst_ip_pattern()
    {
        _dst_ip_pattern = get_console()->prompt([this](string_t input)
            {
                update_generator(
                    _flow_label_pattern,
                    _src_ip_pattern,
                    input);

                return input;

            },
            "Enter Destination-Address Pattern",
                _dst_ip_pattern,
                _dst_ip_pattern);

    } /* prompt_dst_ip_pattern */

    /*---------------------------------------------------------------------- */

    void ip_v6_frame_setup::update_generator(
        string_t flow_label_pattern,
        string_t src_ip_pattern,
        string_t dst_ip_pattern)
    {
        safe_delete(_generator);

        _generator = new ip_v6_frame_generator_t(
            _traffic_class,
            flow_label_pattern,
            10,
            _next_header,
            _hop_limit,
            src_ip_pattern,
            dst_ip_pattern);

        // Update payload in order to have it's
        // pseudo header re-assigned.
        _payload->update_generator();

        if (_payload->get_generator() != NULL)
        {
            ((ip_v6_frame_generator_t*)_generator)->
                get_payload()->add_generator(_payload->get_generator());
        }

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
