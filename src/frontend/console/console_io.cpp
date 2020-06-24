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

#include "../../../include/assert.h"
#include "../../../include/constants.h"
#include "../../../include/frontend/console/console_io.h"

namespace hyenae::frontend::console
{
    /*---------------------------------------------------------------------- */

    const string_t console_io::ANSI_FG_RESET = "\u001B[0m";
    const string_t console_io::ANSI_FG_BLACK = "\u001B[30m";
    const string_t console_io::ANSI_FG_RED = "\u001B[31m";
    const string_t console_io::ANSI_FG_GREEN = "\u001B[32m";
    const string_t console_io::ANSI_FG_YELLOW = "\u001B[33m";
    const string_t console_io::ANSI_FG_BLUE = "\u001B[34m";
    const string_t console_io::ANSI_FG_PURPLE = "\u001B[35m";
    const string_t console_io::ANSI_FG_CYAN = "\u001B[36m";
    const string_t console_io::ANSI_FG_WHITE = "\u001B[37m";

    /*---------------------------------------------------------------------- */

    const string_t console_io::ANSI_BG_RESET = ANSI_FG_RESET;
    const string_t console_io::ANSI_BG_BLACK = "\u001B[40m";
    const string_t console_io::ANSI_BG_RED = "\u001B[41m";
    const string_t console_io::ANSI_BG_GREEN = "\u001B[42m";
    const string_t console_io::ANSI_BG_YELLOW = "\u001B[43m";
    const string_t console_io::ANSI_BG_BLUE = "\u001B[44m";
    const string_t console_io::ANSI_BG_PURPLE = "\u001B[45m";
    const string_t console_io::ANSI_BG_CYAN = "\u001B[46m";
    const string_t console_io::ANSI_BG_WHITE = "\u001B[47m";

    /*---------------------------------------------------------------------- */

    console_io::console_io(app_config* config)
    {
        assert::argument_not_null(config, "config");

        _config = config;

    } /* console_io */

    /*---------------------------------------------------------------------- */
    
    void console_io::header_out(string_t title)
    {
        string_t menu_info = "";
        string_t app_info = "";
        string_t titlebar = "";
        string_t header = "";

        clear();

        // Menu Info
        menu_info.append(" >> ");
        menu_info.append(title);

        // App Info
        app_info.append(constants::APP_NAME);
        app_info.append(" - Version ");
        app_info.append(constants::APP_VERSION);
        app_info.append(" ");

        // Titlebar
        titlebar.append(menu_info);
        pad_to_margin(titlebar, MENU_WIDTH - app_info.size());
        titlebar.append(app_info);
        titlebar = ansi_color(titlebar, ANSI_FG_BLACK, ANSI_BG_WHITE);

        // Header
        header.append("\n");
        pad_to_margin(header, BASE_MARGIN + 1);
        header.append(titlebar);
        header.append("\n");

        out(header);

        if (_config->get_console_frontend_terminal_colors())
        {
            out("\n");
        }
        else
        {
            separator_out(false, true);
        }

    } /* header_out */

    /*---------------------------------------------------------------------- */

    void console_io::separator_out(bool nl_before, bool nl_after)
    {
        string_t text = "";

        if (nl_before)
        {
            text.append("\n");
        }

        pad_to_margin(text, BASE_MARGIN + text.size());

        for (int i = 0; i < (int)MENU_WIDTH; i++)
        {
            if (_config->get_console_frontend_line_chararacters())
            {
                #if defined(CHARSET_ASCII)
                    text.append(string_t(1, (char)205));
                #elif defined (CHARSET_UNICODE)
                    text.append("\u2550");
                #else
                    text.append("-");
                #endif
            }
            else
            {
                text.append("-");
            }
        }

        if (nl_after)
        {
            text.append("\n\n");
        }

        out(text);

    } /* separator_out */

    /*---------------------------------------------------------------------- */

    void console_io::menu_separator_out(bool nl_before, bool nl_after)
    {
        string_t text = "";

        if (nl_before)
        {
            text.append("\n");
        }

        pad_to_margin(text, BASE_MARGIN + text.size());
        pad_to_margin(text, MENU_ITEM_MARGIN + text.size());

        for (int i = 0; i < (int)MENU_WIDTH / 2; i++)
        {
            text.append(". ");
        }
        
        if (nl_after)
        {
            text.append("\n\n");
        }

        out(text);

    } /* menu_separator_out */

    /*---------------------------------------------------------------------- */

    void console_io::menu_item_out(
        const string_t& choice,
        bool selected,
        const string_t& caption,
        const string_t& hint,
        const string_t& info,
        size_t item_count)
    {
        string_t text = "";

        pad_to_margin(text, BASE_MARGIN + text.size());
        pad_to_margin(text, MENU_ITEM_MARGIN + text.size());

        text.append("[");
        
        // TODO: Refactor, pass max choice length instead and calculate
        //       spaces to pad.
        if (choice.size() == 1 && item_count > 9)
        {
            text.append(" ");
        }

        text.append(choice);
        text.append("] ");
        text.append(selected ? ">" : " ");
        text.append(" ");
        text.append(caption);

        if (hint != "")
        {
            text.append(" (");
            text.append(hint);
            text.append(")");
        }

        if (info != "")
        {
            pad_to_margin(text, MENU_ITEM_INFO_MARGIN);

            text.append(": ");
            text.append(info);
        }

        text.append("\n");

        out(text);

    } /* menu_item_out */

    /*---------------------------------------------------------------------- */

    void console_io::info_out(string_t message, bool menu_item_margin)
    {
        prefixed_out("(i)", message, menu_item_margin);

    } /* info_out */

    /*---------------------------------------------------------------------- */

    void console_io::error_out(string_t message, bool menu_item_margin)
    {
        prefixed_out(
            ansi_color("(!)", ANSI_FG_RED),
            ansi_color(message, ANSI_FG_RED),
            menu_item_margin);

    } /* error_out */

    /*---------------------------------------------------------------------- */

    void console_io::task_out(string_t name)
    {
        string_t text = "";

        pad_to_margin(text, MENU_ITEM_MARGIN);

        text.append("* ");
        text.append(name);
        text.append("\n");

        out(text);

    } /* tas_out */

    /*---------------------------------------------------------------------- */

    bool console_io::task_out(string_t name, func_t<bool()> task)
    {
        string_t text = "";
        string_t error_msg;

        try
        {
            pad_to_margin(text, MENU_ITEM_MARGIN);

            text.append("* ");
            text.append(name);
            pad_to_margin(text, MENU_ITEM_INFO_MARGIN);

            out(text);

            if (task())
            {
                out("(" + ansi_color("OK", ANSI_FG_GREEN) + ")\n");

                return true;
            }
            else
            {
                out("(" + ansi_color("FAILED", ANSI_FG_RED) + ")\n");

                return false;
            }
        }
        catch (const exception_t& exception)
        {
            error_msg = exception.what();
        }

        if (error_msg != "")
        {
            out("(" + ansi_color("FAILED", ANSI_FG_RED) + ")\n");

            error_out(error_msg, true);

            return false;
        }

        return true;

    } /* task_out */

    /*---------------------------------------------------------------------- */

    void console_io::result_out(string_t name, string_t value)
    {
        string_t text = "";

        pad_to_margin(text, MENU_ITEM_MARGIN);

        text.append("- ");
        text.append(name);

        pad_to_margin(text, MENU_ITEM_INFO_MARGIN);

        text.append(": ");
        text.append(value);
        text.append("\n");

        out(text);

    } /* result_out */

    /*---------------------------------------------------------------------- */

    void console_io::prompt_out(string_t prompt, string_t hint)
    {
        string_t text = "\n";

        pad_to_margin(text, BASE_MARGIN + 1);

        text.append("> ");
        text.append(prompt);

        if (hint != "")
        {
            if (prompt != "")
            {
                text.append(" ");
            }

            text.append("[");
            text.append(hint);
            text.append("]");
        }

        text.append(": ");

        out(text);

    } /* prompt_out */

    /*---------------------------------------------------------------------- */

    string_t console_io::prompt(
        string_t prompt, string_t hint, string_t default_value)
    {
        string_t input;

        prompt_out(prompt, hint);

        input = in();

        if (input != "")
        {
            return input;
        }
        else
        {
            return default_value;
        }

    } /* prompt_out */

    /*---------------------------------------------------------------------- */

    string_t console_io::prompt(
        func_t<string_t(string_t input)> parse,
        string_t prompt,
        string_t hint,
        string_t default_value)
    {
        string_t input;
        bool success = false;

        while (!success)
        {
            try
            {
                prompt_out(prompt, hint);

                input = in();

                if (input == "")
                {
                    input = default_value;
                }

                parse(input);

                success = true;
            }
            catch (const exception_t& exception)
            {
                error_out(exception.what());
            }
        }

        return input;

    } /* prompt */

    /*---------------------------------------------------------------------- */

    int64_t console_io::prompt(
        int64_t min_value,
        int64_t max_value,
        string_t prompt,
        string_t hint,
        size_t default_choice)
    {
        string_t input;
        int64_t result = 0;
        bool success = false;

        while (!success)
        {
            try
            {
                prompt_out(prompt, hint);

                input = in();

                if (input == "" && default_choice != SIZE_NONE)
                {
                    result = (int64_t) default_choice;
                }
                else
                {
                    result = std::stoll(input);

                    assert::in_range(result >= min_value && result <= max_value);
                }

                success = true;
            }
            catch (const std::out_of_range&)
            {
                error_out(
                    concat("Value out of range: ", input.c_str()).c_str());
            }
            catch (const std::invalid_argument&)
            {
                error_out(concat("Invalid value: ", input.c_str()).c_str());
            }
        }

        return result;

    } /* prompt */

    /*---------------------------------------------------------------------- */

    void console_io::wait_for_key_press(string_t prompt)
    {
        prompt_out("", prompt);

        while (!was_key_pressed());

    } /* wait_for_key_press */

    /*---------------------------------------------------------------------- */

    void console_io::pad_to_margin(string_t& text, size_t margin)
    {
        int pad_len = margin - text.size();

        if (pad_len > 0)
        {
            text.append(string_t(pad_len, ' '));
        }

    } /* pad_to_margin */

    /*---------------------------------------------------------------------- */

    void console_io::prefixed_out(
        string_t prefix, string_t message, bool menu_item_margin)
    {
        string_t text = "\n";

        pad_to_margin(text, BASE_MARGIN + text.size());

        if (menu_item_margin)
        {
            pad_to_margin(text, MENU_ITEM_MARGIN + text.size());
        }

        text.append(prefix);
        text.append(" ");
        text.append(message);
        text.append("\n");

        out(text);

    } /* prefixed_out */

    /*---------------------------------------------------------------------- */

    string_t console_io::ansi_color(
        string_t text, string_t ansi_fg, string_t ansi_bg)
    {
        string_t colored = "";
        
        if (_config->get_console_frontend_terminal_colors())
        {
            colored.append(ansi_bg);
            colored.append(ansi_fg);
            colored.append(text);
            colored.append(ANSI_FG_RESET);
            colored.append(ANSI_BG_RESET);

            return colored;
        }
        else
        {
            return text;
        }

    } /* text_color */

    /*---------------------------------------------------------------------- */

} /* hyenae::frontend::console */
