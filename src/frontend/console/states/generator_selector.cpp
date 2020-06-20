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

#include "../../../../include/frontend/console/states/generator_selector.h"
#include "../../../../include/frontend/console/states/ethernet_frame_setup.h"
#include "../../../../include/frontend/console/states/arp_frame_setup.h"
#include "../../../../include/frontend/console/states/ip_v4_frame_setup.h"
#include "../../../../include/frontend/console/states/ip_v6_frame_setup.h"
#include "../../../../include/frontend/console/states/icmp_v4_frame_setup.h"
#include "../../../../include/frontend/console/states/icmp_v6_frame_setup.h"
#include "../../../../include/frontend/console/states/icmp_echo_payload_setup.h"
#include "../../../../include/frontend/console/states/udp_frame_setup.h"
#include "../../../../include/frontend/console/states/tcp_frame_setup.h"
#include "../../../../include/frontend/console/states/text_buffer_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    generator_selector::generator_selector(
        string_t title,
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent) :
            generator_setup(context, console_io, parent)
    {
        _title = title;

        _generator_flags =
            GFLAG_ETHERNET_FRAME |
            GFLAG_TEXT_BUFFER;

    } /* generator_selector */

    /*---------------------------------------------------------------------- */

    generator_selector::generator_selector(
        string_t title,
        console_app_state_context* context,
        console_io* console_io,
        generator_setup* parent) :
            generator_setup(context, console_io, parent)
    {
        _title = title;

        _generator_flags =
            GFLAG_TEXT_BUFFER;
        
    } /* generator_selector */

    /*---------------------------------------------------------------------- */

    generator_selector::generator_selector(
        string_t title,
        console_app_state_context* context,
        console_io* console_io,
        ethernet_frame_setup* parent) :
            generator_setup(context, console_io, parent)
    {
        _title = title;

        _generator_flags =
            GFLAG_ARP_FRAME |
            GFLAG_IP_V4_FRAME |
            GFLAG_IP_V6_FRAME |
            GFLAG_TEXT_BUFFER;

    } /* generator_selector */

    /*---------------------------------------------------------------------- */

    generator_selector::generator_selector(
        string_t title,
        console_app_state_context* context,
        console_io* console_io,
        ip_v4_frame_setup* parent) :
            generator_setup(context, console_io, parent)
    {
        _title = title;

        _generator_flags =
            GFLAG_ICMP_V4_OVER_IP_V4_FRAME |
            GFLAG_TCP_OVER_IP_V4_FRAME |
            GFLAG_UDP_OVER_IP_V4_FRAME |
            GFLAG_TEXT_BUFFER;

    } /* generator_selector */

    /*---------------------------------------------------------------------- */

    generator_selector::generator_selector(
        string_t title,
        console_app_state_context* context,
        console_io* console_io,
        ip_v6_frame_setup* parent) :
        generator_setup(context, console_io, parent)
    {
        _title = title;

        _generator_flags =
            GFLAG_ICMP_V4_OVER_IP_V6_FRAME |
            GFLAG_ICMP_V6_FRAME |
            GFLAG_TCP_OVER_IP_V6_FRAME |
            GFLAG_UDP_OVER_IP_V6_FRAME |
            GFLAG_TEXT_BUFFER;

    } /* generator_selector */

    /*---------------------------------------------------------------------- */

    generator_selector::generator_selector(
        string_t title,
        console_app_state_context* context,
        console_io* console_io,
        icmp_v4_frame_setup* parent) :
            generator_setup(context, console_io, parent)
    {
        _title = title;

        _generator_flags =
            GFLAG_ICMP_V4_ECHO_PAYLOAD;

    } /* generator_selector */

    /*---------------------------------------------------------------------- */

    generator_selector::generator_selector(
        string_t title,
        console_app_state_context* context,
        console_io* console_io,
        icmp_v6_frame_setup* parent) :
        generator_setup(context, console_io, parent)
    {
        _title = title;

        _generator_flags =
            GFLAG_ICMP_V6_ECHO_PAYLOAD;

    } /* generator_selector */

    /*---------------------------------------------------------------------- */

    generator_selector::~generator_selector()
    {
        for (auto item : _menu_items)
        {
            delete item.first;
            delete item.second;
        }

        safe_delete(_menu);
        safe_delete(_none_item);

    } /* ~generator_selector */

    /*---------------------------------------------------------------------- */

    bool generator_selector::run()
    {
        if (!_init)
        {
            // Initialize when entered in order to prevent a
            // stack-overflow because of generator_states that
            // might also use generator_selectors.

            inizialize();

            _init = true;
        }
        
        update_menu_items();

        _menu->set_start_state(get_start_state());

        console_menu::item* choice = _menu->prompt(_selected_item);

        if (choice != _menu->get_start_state_item() &&
            choice != _menu->get_parent_state_item() &&
            choice != NULL)
        {
            if (choice != _none_item)
            {
                if (_selected_setup != _menu_items[choice])
                {
                    _selected_setup = _menu_items[choice];

                    _selected_setup->on_select();
                }
                else
                {
                    _selected_setup->enter();
                }

                _selected_item = choice;
            }
            else
            {
                _selected_item = NULL;
                _selected_setup = NULL;
            }
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    string_t generator_selector::get_generator_name() const
    {
        if (_selected_setup != NULL)
        {
            return _selected_setup->get_generator_name();
        }
        else
        {
            return "None";
        }

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    generator_selector::data_generator_t*
        generator_selector::get_generator() const
    {
        if (_selected_setup != NULL)
        {
            return _selected_setup->get_generator();
        }
        else
        {
            return NULL;
        }
        
    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void generator_selector::update_generator()
    {
        if (_selected_setup != NULL)
        {
            _selected_setup->update_generator();
        }

    } /* update_generator */

    /*---------------------------------------------------------------------- */

    void generator_selector::inizialize()
    {
        using namespace model::generators::protocols;

        generator_setup* setup = NULL;

        _menu = new console_menu(get_console(), _title, this, get_parent());

        // None
        _none_item = new console_menu::item("None");
        _menu->add_item(_none_item);

        if (_generator_flags & GFLAG_ETHERNET_FRAME)
        {
            // Ethernet-Frame
            setup = new ethernet_frame_setup(
                get_context(), get_console(), get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_IP_V4_FRAME)
        {
            // ARP-Frame
            setup = new arp_frame_setup(
                get_context(),
                get_console(),
                get_parent(),
                (ethernet_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_IP_V4_FRAME)
        {
            // IPv4-Frame
            setup =new ip_v4_frame_setup(
                get_context(),
                get_console(),
                get_parent(),
                (ethernet_frame_setup*) get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_IP_V6_FRAME)
        {
            // IPv6-Frame
            setup =new ip_v6_frame_setup(
                get_context(),
                get_console(),
                get_parent(),
                (ethernet_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_ICMP_V4_OVER_IP_V4_FRAME)
        {
            // ICMPv4 over IPv4 Frame
            setup = new icmp_v4_frame_setup(
                icmp_v4_frame_generator::IP_V4_PROTOCOL,
                get_context(),
                get_console(),
                get_parent(),
                (ip_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_ICMP_V4_OVER_IP_V6_FRAME)
        {
            // ICMPv4 over IPv4 Frame
            setup = new icmp_v4_frame_setup(
                icmp_v4_frame_generator::IP_V6_PROTOCOL,
                get_context(),
                get_console(),
                get_parent(),
                (ip_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_ICMP_V6_FRAME)
        {
            // ICMPv6-Frame
            setup = new icmp_v6_frame_setup(
                icmp_v6_frame_generator::IP_V6_PROTOCOL,
                get_context(),
                get_console(),
                get_parent(),
                (ip_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_ICMP_V4_ECHO_PAYLOAD)
        {
            // ICMPv4-Echo Payload
            setup = new icmp_echo_payload_setup(
                icmp_echo_payload_generator::ICMP_V4_TYPE,
                icmp_echo_payload_generator::ICMP_V4_CODE,
                get_context(),
                get_console(),
                get_parent(),
                (icmp_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_ICMP_V6_ECHO_PAYLOAD)
        {
            // ICMPv6-Echo Payload
            setup = new icmp_echo_payload_setup(
                icmp_echo_payload_generator::ICMP_V6_TYPE,
                icmp_echo_payload_generator::ICMP_V6_CODE,
                get_context(),
                get_console(),
                get_parent(),
                (icmp_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_TCP_OVER_IP_V4_FRAME)
        {
            // TCP over IPv4 Frame
            setup = new tcp_frame_setup(
                tcp_frame_generator::IP_V4_PROTOCOL,
                get_context(),
                get_console(),
                get_parent(),
                (ip_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_TCP_OVER_IP_V6_FRAME)
        {
            // TCP over IPv6 Frame
            setup = new tcp_frame_setup(
                tcp_frame_generator::IP_V6_NEXT_HEADER,
                get_context(),
                get_console(),
                get_parent(),
                (ip_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_UDP_OVER_IP_V4_FRAME)
        {
            // UDP over IPv4 Frame
            setup =new udp_frame_setup(
                udp_frame_generator::IP_V4_PROTOCOL,
                get_context(),
                get_console(),
                get_parent(),
                (ip_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_UDP_OVER_IP_V6_FRAME)
        {
            // UDP over IPv4 Frame
            setup = new udp_frame_setup(
                udp_frame_generator::IP_V6_NEXT_HEADER,
                get_context(),
                get_console(),
                get_parent(),
                (ip_frame_setup*)get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

        if (_generator_flags & GFLAG_TEXT_BUFFER)
        {
            // Text-Buffer
            setup = new text_buffer_setup(
                get_context(), get_console(), get_parent());
            setup->set_start_state(get_start_state());
            add_generator(setup);
        }

    } /* inizialize */

    /*---------------------------------------------------------------------- */

    void generator_selector::update_menu_items()
    {
        _none_item->set_selected(false);

        for (auto item : _menu_items)
        {
            item.first->set_selected(false);
            item.first->set_hint("");
        }

        if (_selected_setup != NULL)
        {
            for (auto item : _menu_items)
            {
                if (item.second == _selected_setup)
                {
                    item.first->set_selected(true);
                    item.first->set_hint("...");

                    break;
                }
            }
        }
        else
        {
            _menu->select_all(false);
            _none_item->set_selected(true);
        }

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void generator_selector::add_generator(generator_setup* setup_state)
    {
        console_menu::item* menu_item = NULL;

        menu_item = new console_menu::item(
            setup_state->get_generator_name());
        
        _menu_items[menu_item] = setup_state;
        _menu->add_item(menu_item);

    } /* add_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
