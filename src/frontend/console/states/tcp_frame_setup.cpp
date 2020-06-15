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

#include "../../../../include/frontend/console/states/tcp_frame_setup.h"

namespace hyenae::frontend::console::states
{
	/*---------------------------------------------------------------------- */

	tcp_frame_setup::tcp_frame_setup(
		console_app_state_context* context,
		console_io* console_io,
		console_app_state* parent,
		ip_frame_setup* ip_frame_setup) :
			generator_setup(context, console_io, parent)
	{
		assert::argument_not_null(
			_ip_frame_setup = ip_frame_setup, "ip_frame_setup");
		
		_menu = new console_menu(
			console_io, get_generator_name() + " Setup");

		_payload = new generator_selector(
			"Payload Setup", context, console_io, this);

		// Default values
		_src_port_pattern = "*****";
		_dst_port_pattern = "*****";
		_seq_num_pattern = "*****";
		_ack_num_pattern = "*****";
		_cwr_flag = false;
		_ece_flag = false;
		_urg_flag = false;
		_ack_flag = false;
		_psh_flag = false;
		_rst_flag = false;
		_syn_flag = false;
		_fin_flag = false;
		_win_size_pattern = "*****";
		_urg_pointer_pattern = "*****";

		// Source Port
		_src_port_pattern_item = new console_menu::item("Source Port");
		_menu->add_item(_src_port_pattern_item);

		// Destination Port
		_dst_port_pattern_item = new console_menu::item("Destination Port");
		_menu->add_item(_dst_port_pattern_item);

		// Sequence Number
		_seq_num_pattern_item = new console_menu::item("Sequence Number");
		_menu->add_item(_seq_num_pattern_item);

		// Acknowledge Number
		_ack_num_pattern_item = new console_menu::item("Acknowledge Number");
		_menu->add_item(_ack_num_pattern_item);

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

		// Window Size
		_win_size_pattern_item = new console_menu::item("Window Size");
		_menu->add_item(_win_size_pattern_item);

		// Urgent Pointer
		_urg_pointer_pattern_item = new console_menu::item("Urgent Pointer");
		_menu->add_item(_urg_pointer_pattern_item);

		// Payload
		_payload_item =
			new console_menu::item("Payload");
		_menu->add_item(_payload_item);

		// Back
		_back_item = new console_menu::item("Back");
		_menu->add_item(_back_item);

		update_generator();

	} /* tcp_frame_setup */

	/*---------------------------------------------------------------------- */

	tcp_frame_setup::~tcp_frame_setup()
	{
		safe_delete(_menu);
		safe_delete(_src_port_pattern_item);
		safe_delete(_dst_port_pattern_item);
		safe_delete(_seq_num_pattern_item);
		safe_delete(_ack_num_pattern_item);
		safe_delete(_cwr_flag_item);
		safe_delete(_ece_flag_item);
		safe_delete(_urg_flag_item);
		safe_delete(_ack_flag_item);
		safe_delete(_psh_flag_item);
		safe_delete(_rst_flag_item);
		safe_delete(_syn_flag_item);
		safe_delete(_fin_flag_item);
		safe_delete(_payload_item);
		safe_delete(_win_size_pattern_item);
		safe_delete(_urg_pointer_pattern_item);
		safe_delete(_back_item);
		safe_delete(_generator);
		safe_delete(_payload);

	} /* ~tcp_frame_setup */

	/*---------------------------------------------------------------------- */

	bool tcp_frame_setup::run()
	{
		update_generator();
		update_menu_items();

		console_menu::item* choice = _menu->prompt();

		if (choice == _src_port_pattern_item)
		{
			prompt_src_port_pattern();
		}
		else if (choice == _dst_port_pattern_item)
		{
			prompt_dst_port_pattern();
		}
		else if (choice == _seq_num_pattern_item)
		{
			prompt_seq_num_pattern();
		}
		else if (choice == _ack_num_pattern_item)
		{
			prompt_ack_num_pattern();
		}
		else if (choice == _cwr_flag_item)
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
		else if (choice == _win_size_pattern_item)
		{
			prompt_win_size_pattern();
		}
		else if (choice == _urg_pointer_pattern_item)
		{
			prompt_urg_pointer_pattern();
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

	string_t tcp_frame_setup::get_generator_name() const
	{
		return "TCP-Frame";

	} /* get_generator_name */

	/*---------------------------------------------------------------------- */

	tcp_frame_setup::data_generator_t*
		tcp_frame_setup::get_generator() const
	{
		return _generator;

	} /* get_generator */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::update_generator()
	{
		update_generator(
			_src_port_pattern,
			_dst_port_pattern,
			_seq_num_pattern,
			_ack_num_pattern,
			_win_size_pattern,
			_urg_pointer_pattern);

	} /* update_generator */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::on_select()
	{
		_ip_frame_setup->set_protocol(PROTOCOL);

	} /* on_select */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::update_menu_items()
	{
		_src_port_pattern_item->set_info(_src_port_pattern);
		_dst_port_pattern_item->set_info(_dst_port_pattern);
		_seq_num_pattern_item->set_info(_seq_num_pattern);
		_ack_num_pattern_item->set_info(_ack_num_pattern);
		_cwr_flag_item->set_info(_cwr_flag ? "On" : "Off");
		_ece_flag_item->set_info(_ece_flag ? "On" : "Off");
		_urg_flag_item->set_info(_urg_flag ? "On" : "Off");
		_ack_flag_item->set_info(_ack_flag ? "On" : "Off");
		_psh_flag_item->set_info(_psh_flag ? "On" : "Off");
		_rst_flag_item->set_info(_rst_flag ? "On" : "Off");
		_syn_flag_item->set_info(_syn_flag ? "On" : "Off");
		_fin_flag_item->set_info(_fin_flag ? "On" : "Off");
		_win_size_pattern_item->set_info(_win_size_pattern);
		_urg_pointer_pattern_item->set_info(_urg_pointer_pattern);
		_payload_item->set_info(_payload->get_generator_name());

	} /* update_menu_items */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_src_port_pattern()
	{
		_src_port_pattern = get_console()->prompt([this](string_t input)
		{
			update_generator(
				input,
				_dst_port_pattern,
				_seq_num_pattern,
				_ack_num_pattern,
				_win_size_pattern,
				_urg_pointer_pattern);

			return input;

		},
		"Enter Source Port Pattern",
			_src_port_pattern,
			_src_port_pattern);

	} /* prompt_src_port_pattern */

/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_dst_port_pattern()
	{
		_dst_port_pattern = get_console()->prompt([this](string_t input)
		{
			update_generator(
				_src_port_pattern,
				input,
				_seq_num_pattern,
				_ack_num_pattern,
				_win_size_pattern,
				_urg_pointer_pattern);

			return input;

		},
		"Enter Destination Port Pattern",
			_dst_port_pattern,
			_dst_port_pattern);

	} /* prompt_src_port_pattern */

	/*---------------------------------------------------------------------- */
	void tcp_frame_setup::prompt_seq_num_pattern()
	{
		_seq_num_pattern = get_console()->prompt([this](string_t input)
		{
			update_generator(
				_src_port_pattern,
				_dst_port_pattern,
				input,
				_ack_num_pattern,
				_win_size_pattern,
				_urg_pointer_pattern);

			return input;

		},
		"Enter Sequence Number Pattern",
			_seq_num_pattern,
			_seq_num_pattern);

	} /* prompt_seq_num_pattern */

	void tcp_frame_setup::prompt_ack_num_pattern()
	{
		_ack_num_pattern = get_console()->prompt([this](string_t input)
		{
			update_generator(
				_src_port_pattern,
				_dst_port_pattern,
				_seq_num_pattern,
				input,
				_win_size_pattern,
				_urg_pointer_pattern);

			return input;

		},
		"Enter Acknowledge Number Pattern",
			_ack_num_pattern,
			_ack_num_pattern);

	} /* prompt_ack_num_pattern */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_cwr_flag()
	{
		_cwr_flag = get_console()->prompt(
			0, 1, "CWR-Flag", "0 = Off, 1 = On");

	} /* prompt_cwr_flag */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_ece_flag()
	{
		_ece_flag = get_console()->prompt(
			0, 1, "ECE-Flag", "0 = Off, 1 = On");

	} /* prompt_ece_flag */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_urg_flag()
	{
		_urg_flag = get_console()->prompt(
			0, 1, "URG-Flag", "0 = Off, 1 = On");

	} /* prompt_urg_flag */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_ack_flag()
	{
		_ack_flag = get_console()->prompt(
			0, 1, "ACK-Flag", "0 = Off, 1 = On");

	} /* prompt_ack_flag */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_psh_flag()
	{
		_psh_flag = get_console()->prompt(
			0, 1, "PSH-Flag", "0 = Off, 1 = On");

	} /* prompt_psh_flag */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_rst_flag()
	{
		_rst_flag = get_console()->prompt(
			0, 1, "RST-Flag", "0 = Off, 1 = On");

	} /* prompt_rst_flag */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_syn_flag()
	{
		_syn_flag = get_console()->prompt(
			0, 1, "SYN-Flag", "0 = Off, 1 = On");

	} /* prompt_syn_flag */
	
	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_fin_flag()
	{
		_fin_flag = get_console()->prompt(
			0, 1, "FIN-Flag", "0 = Off, 1 = On");

	} /* prompt_fin_flag */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_win_size_pattern()
	{
		_win_size_pattern = get_console()->prompt([this](string_t input)
		{
			update_generator(
				_src_port_pattern,
				_dst_port_pattern,
				_seq_num_pattern,
				_ack_num_pattern,
				input,
				_urg_pointer_pattern);

			return input;

		},
		"Enter Window Size Pattern",
			_win_size_pattern,
			_win_size_pattern);

	} /* prompt_win_size_pattern */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::prompt_urg_pointer_pattern()
	{
		_urg_pointer_pattern = get_console()->prompt([this](string_t input)
		{
			update_generator(
				_src_port_pattern,
				_dst_port_pattern,
				_seq_num_pattern,
				_ack_num_pattern,
				_win_size_pattern,
				input);

			return input;

		},
		"Enter Urgent Pointer Pattern",
			_urg_pointer_pattern,
			_urg_pointer_pattern);

	} /* prompt_urg_pointer_pattern */

	/*---------------------------------------------------------------------- */

	void tcp_frame_setup::update_generator(
		string_t src_port_pattern,
		string_t dst_port_pattern,
		string_t seq_num_pattern,
		string_t ack_num_pattern,
		string_t win_size_pattern,
		string_t urg_pointer_pattern)
	{
		safe_delete(_generator);

		_generator = new tcp_frame_generator_t(
			_ip_frame_setup->get_pseudo_header(),
			src_port_pattern,
			10,
			dst_port_pattern,
			10,
			seq_num_pattern,
			10,
			ack_num_pattern,
			10,
			_cwr_flag,
			_ece_flag,
			_urg_flag,
			_ack_flag,
			_psh_flag,
			_rst_flag,
			_syn_flag,
			_fin_flag,
			win_size_pattern,
			10,
			urg_pointer_pattern,
			10);

		if (_payload->get_generator() != NULL)
		{
			((tcp_frame_generator_t*)_generator)->
				get_payload()->add_generator(_payload->get_generator());
		}

	} /* update_generator */

	/*---------------------------------------------------------------------- */

} /* hyenae::frontend::console::states */
