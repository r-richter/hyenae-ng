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

#include "../../../../include/frontend/console/states/tcp_flags_setup.h"

namespace hyenae::frontend::console::states
{
    /*---------------------------------------------------------------------- */

    tcp_flags_setup::tcp_flags_setup(
        console_app_state_context* context,
        console_io* console_io,
        console_app_state* parent) :
            console_app_state(
                context,
                console_io,
                parent)
    {
        _menu = new console_menu(
            console_io, "TCP-Flags Setup");
        
        _cwr_flag = false;
        _ece_flag = false;
        _urg_flag = false;
        _ack_flag = false;
        _psh_flag = false;
        _rst_flag = false;
        _syn_flag = false;
        _fin_flag = false;

        // CWR-Flag
        _cwr_flag_item = new console_menu::item("CWR-Flag");
        _menu->add_item(_cwr_flag_item);

        // ECE-Flag
        _ece_flag_item = new console_menu::item("ECE-Flag");
        _menu->add_item(_ece_flag_item);

        // URG-Flag
        _urg_flag_item = new console_menu::item("URG-Flag");
        _menu->add_item(_urg_flag_item);

        // ACK-Flag
        _ack_flag_item = new console_menu::item("ACK-Flag");
        _menu->add_item(_ack_flag_item);

        // PSH-Flag
        _psh_flag_item = new console_menu::item("PSH-Flag");
        _menu->add_item(_psh_flag_item);

        // RST-Flag
        _rst_flag_item = new console_menu::item("RST-Flag");
        _menu->add_item(_rst_flag_item);

        // SYN-Flag
        _syn_flag_item = new console_menu::item("SYN-Flag");
        _menu->add_item(_syn_flag_item);

        // FIN-Flag
        _fin_flag_item = new console_menu::item("FIN-Flag");
        _menu->add_item(_fin_flag_item);

    } /* tcp_flags_setup */

    /*---------------------------------------------------------------------- */

    tcp_flags_setup::~tcp_flags_setup()
    {
        safe_delete(_menu);
        safe_delete(_cwr_flag_item);
        safe_delete(_ece_flag_item);
        safe_delete(_urg_flag_item);
        safe_delete(_ack_flag_item);
        safe_delete(_psh_flag_item);
        safe_delete(_rst_flag_item);
        safe_delete(_syn_flag_item);
        safe_delete(_fin_flag_item);

    } /* ~tcp_flags_setup */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::run()
    {
        update_menu_items();

        console_menu::item* choice = _menu->prompt();

        if (choice == _cwr_flag_item)
        {
            prompt_cwr_flag();
        }
        else if (choice == _ece_flag_item)
        {
            prompt_ece_flag();
        }
        else if (choice == _urg_flag_item)
        {
            prompt_urg_flag();
        }
        else if (choice == _ack_flag_item)
        {
            prompt_ack_flag();
        }
        else if (choice == _psh_flag_item)
        {
            prompt_psh_flag();
        }
        else if (choice == _rst_flag_item)
        {
            prompt_rst_flag();
        }
        else if (choice == _syn_flag_item)
        {
            prompt_syn_flag();
        }
        else if (choice == _fin_flag_item)
        {
            prompt_fin_flag();
        }
        else if (choice == _menu->get_back_item())
        {
            back();
        }

        return true;

    } /* run */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_cwr_flag() const
    {
        return _cwr_flag;

    } /* get_cwr_flag */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_ece_flag() const
    {
        return _ece_flag;

    } /* get_ece_flag */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_urg_flag() const
    {
        return _urg_flag;

    } /* get_urg_flag */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_ack_flag() const
    {
        return _ack_flag;

    } /* get_ack_flag */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_psh_flag() const
    {
        return _psh_flag;

    } /* get_psh_flag */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_rst_flag() const
    {
        return _rst_flag;

    } /* get_rst_flag */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_syn_flag() const
    {
        return _syn_flag;

    } /* get_syn_flag */

    /*---------------------------------------------------------------------- */

    bool tcp_flags_setup::get_fin_flag() const
    {
        return _fin_flag;

    } /* get_fin_flag */

    /*---------------------------------------------------------------------- */

    string_t tcp_flags_setup::get_flags_info() const
    {
        string_t info = "";

        info.append(_cwr_flag ? "CWR " : "");
        info.append(_ece_flag ? "ECE " : "");
        info.append(_urg_flag ? "URG " : "");
        info.append(_ack_flag ? "ACK " : "");
        info.append(_psh_flag ? "PSH " : "");
        info.append(_rst_flag ? "RST " : "");
        info.append(_syn_flag ? "SYN " : "");
        info.append(_fin_flag ? "FIN " : "");

        if (info.size() == 0)
        {
            info.append("None");
        }

        return info;

    } /* get_flags_info */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::update_menu_items()
    {
        _cwr_flag_item->set_info(_cwr_flag ? "On" : "Off");
        _ece_flag_item->set_info(_ece_flag ? "On" : "Off");
        _urg_flag_item->set_info(_urg_flag ? "On" : "Off");
        _ack_flag_item->set_info(_ack_flag ? "On" : "Off");
        _psh_flag_item->set_info(_psh_flag ? "On" : "Off");
        _rst_flag_item->set_info(_rst_flag ? "On" : "Off");
        _syn_flag_item->set_info(_syn_flag ? "On" : "Off");
        _fin_flag_item->set_info(_fin_flag ? "On" : "Off");

    } /* update_menu_items */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_cwr_flag()
    {
        _cwr_flag = get_console()->prompt(
            0, 1, "CWR-Flag", "0 = Off, 1 = On");

    } /* prompt_cwr_flag */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_ece_flag()
    {
        _ece_flag = get_console()->prompt(
            0, 1, "ECE-Flag", "0 = Off, 1 = On");

    } /* prompt_ece_flag */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_urg_flag()
    {
        _urg_flag = get_console()->prompt(
            0, 1, "URG-Flag", "0 = Off, 1 = On");

    } /* prompt_urg_flag */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_ack_flag()
    {
        _ack_flag = get_console()->prompt(
            0, 1, "ACK-Flag", "0 = Off, 1 = On");

    } /* prompt_ack_flag */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_psh_flag()
    {
        _psh_flag = get_console()->prompt(
            0, 1, "PSH-Flag", "0 = Off, 1 = On");

    } /* prompt_psh_flag */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_rst_flag()
    {
        _rst_flag = get_console()->prompt(
            0, 1, "RST-Flag", "0 = Off, 1 = On");

    } /* prompt_rst_flag */

    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_syn_flag()
    {
        _syn_flag = get_console()->prompt(
            0, 1, "SYN-Flag", "0 = Off, 1 = On");

    } /* prompt_syn_flag */
    
    /*---------------------------------------------------------------------- */

    void tcp_flags_setup::prompt_fin_flag()
    {
        _fin_flag = get_console()->prompt(
            0, 1, "FIN-Flag", "0 = Off, 1 = On");

    } /* prompt_fin_flag */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
