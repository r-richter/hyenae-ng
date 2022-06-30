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

#include "../../../../include/frontend/console/states/ethernet_frame_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    ethernet_frame_setup::ethernet_frame_setup(
        console_app_state_context* context,
        console_app_config* config,
        console_io* console_io,
        console_app_state* parent) :
            generator_setup(context, config, console_io, parent)
    {
        _menu = new console_menu(
            console_io, get_generator_name() + " Setup", this, parent);

        _payload = new generator_selector(
            "Payload Setup", context, config, console_io, this);

        // Default values
        _add_preamble_sfd = false;
        _dst_mac_pattern = address_generator_t::RAND_MAC_PATTERN;
        _src_mac_pattern = address_generator_t::RAND_MAC_PATTERN;
        _type = 0;
        _add_fcs = false;

        // Preamble & SFD
        _add_preamble_sfd_item = new console_menu::item("Preamble & SFD");
        _menu->add_item(_add_preamble_sfd_item);

        // Destination-MAC
        _dst_mac_pattern_item = new console_menu::item("Destination-Address");
        _menu->add_item(_dst_mac_pattern_item);

        // Source-MAC
        _src_mac_pattern_item = new console_menu::item("Source-Address");
        _menu->add_item(_src_mac_pattern_item);

        // Type
        _type_item = new console_menu::item("Type");
        _menu->add_item(_type_item);

        // FCS
        _add_fcs_item = new console_menu::item("FCS");
        _menu->add_item(_add_fcs_item);

        // Payload
        _payload_item =
            new console_menu::item("Payload");
        _menu->add_item(_payload_item);

        update_generator();

    } /* ethernet_frame_setup */

    /*---------------------------------------------------------------------- */

    ethernet_frame_setup::~ethernet_frame_setup()
    {
        safe_delete(_menu);
        safe_delete(_add_preamble_sfd_item);
        safe_delete(_dst_mac_pattern_item);
        safe_delete(_src_mac_pattern_item);
        safe_delete(_type_item);
        safe_delete(_add_fcs_item);
        safe_delete(_payload_item);
        safe_delete(_generator);
        safe_delete(_payload);

    } /* ~ethernet_frame_setup */

    /*---------------------------------------------------------------------- */

    bool ethernet_frame_setup::run()
    {
        update_generator();
        update_menu_items();

        _menu->set_start_state(get_start_state());
        _payload->set_start_state(get_start_state());

        console_menu::item* choice = _menu->prompt();

        if (choice == _add_preamble_sfd_item)
        {
            prompt_add_preamble_sfd();
        }
        else if (choice == _dst_mac_pattern_item)
        {
            prompt_dst_mac_pattern();
        }
        else if (choice == _src_mac_pattern_item)
        {
            prompt_src_mac_pattern();
        }
        else if (choice == _type_item)
        {
            prompt_type();
        }
        else if (choice == _add_fcs_item)
        {
            prompt_add_fcs();
        }
        else if (choice == _payload_item)
        {
            _payload->enter();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    uint16_t ethernet_frame_setup::get_type() const
    {
        return _type;

    } /* get_type */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::set_type(uint16_t type)
    {
        _type = type;

    } /* set_type */

    /*---------------------------------------------------------------------- */

    string_t ethernet_frame_setup::get_generator_name() const
    {
        return "Ethernet-Frame";

    } /* get_generator_name */

    /*---------------------------------------------------------------------- */

    ethernet_frame_setup::data_generator_t*
        ethernet_frame_setup::get_generator() const
    {
        return _generator;

    } /* get_generator */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::update_generator()
    {
        update_generator(_src_mac_pattern, _dst_mac_pattern);

    } /* update_generator */

    /*---------------------------------------------------------------------- */
    
    void ethernet_frame_setup::update_menu_items()
    {
        _add_preamble_sfd_item->set_info(_add_preamble_sfd ? "On" : "Off");
        _dst_mac_pattern_item->set_info(_dst_mac_pattern);
        _src_mac_pattern_item->set_info(_src_mac_pattern);
        _type_item->set_info(std::to_string(_type));
        _add_fcs_item->set_info(_add_fcs ? "On" : "Off");
        _payload_item->set_info(_payload->get_generator_name());

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::prompt_add_preamble_sfd()
    {
        _add_preamble_sfd = get_console()->prompt(
            0, 1, "Enable Preamble & SFD", "0 = Off, 1 = On");

    } /* prompt_add_preamble_sfd */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::prompt_src_mac_pattern()
    {
        _src_mac_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(input, _dst_mac_pattern);

            return input;

        },
        "Enter Source-Address Pattern",
        _src_mac_pattern,
        _src_mac_pattern);

    } /* prompt_src_mac_pattern */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::prompt_dst_mac_pattern()
    {
        _dst_mac_pattern = get_console()->prompt([this](string_t input)
        {
            update_generator(_src_mac_pattern, input);

            return input;

        },
        "Enter Destination-Address Pattern",
        _dst_mac_pattern,
        _dst_mac_pattern);

    } /* prompt_dst_mac_pattern */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::prompt_add_fcs()
    {
        _add_fcs = get_console()->prompt(
            0, 1, "Enable FCS", "0 = Off, 1 = On");

    } /* prompt_add_fcs */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::prompt_type()
    {
        // TODO: Have type entered as hexadecimal number

        _type = (uint16_t) get_console()->prompt(
            0, UINT16_MAX, "Enter Type (Decimal)");

        update_generator();

    } /* prompt_type */

    /*---------------------------------------------------------------------- */

    void ethernet_frame_setup::update_generator(
        string_t src_mac_pattern, string_t dst_mac_pattern)
    {
        safe_delete(_generator);
        
        _generator = new ethernet_frame_generator_t(
            _add_preamble_sfd,
            dst_mac_pattern,
            src_mac_pattern,
            _type,
            _add_fcs);

        _payload->update_generator();

        if (_payload->get_generator() != NULL)
        {
            ((ethernet_frame_generator_t*)_generator)->
                get_payload()->add_generator(_payload->get_generator());
        }

    } /* update_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
