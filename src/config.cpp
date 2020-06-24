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

#include "../include/assert.h"
#include "../include/config.h"

#include <algorithm>

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    config::config(section* root_section)
    {
        assert::argument_not_null(root_section, "root_section");

        _root_section = root_section;

    } /* config */

    /*---------------------------------------------------------------------- */

    config::config(string_t name) : 
        config(new section(name)) {}

    /*---------------------------------------------------------------------- */

    config::~config()
    {
        safe_delete(_root_section);

    } /* ~config */

    /*---------------------------------------------------------------------- */

    config* config::parse(const string_t& text)
    {
        return new config(parse_section(text));

    } /* parse */

    /*---------------------------------------------------------------------- */

    config::section* config::get_root_section() const
    {
        return _root_section;

    } /* get_root_section */

    /*---------------------------------------------------------------------- */

    string_t config::to_string()
    {
        return _root_section->to_string();

    } /* to_string */

    /*---------------------------------------------------------------------- */

    void config::parse_and_replace_root_section(const string_t& text);
    {
        safe_delete(_root_section);

        _root_section = parse_section(text);

    } /* parse_and_replace_root_section */

    /*---------------------------------------------------------------------- */

    config::section* config::parse_section(const string_t& text)
    {
        char chr = 0;
        string_t tmp = "";
        string_t item_name = "";
        string_t item_value = "";
        size_t section_index = 0;
        section* cur_section = NULL;
        vector_t<section*> sections;

        try
        {
            // TODO: Trim parsed names and values

            tmp = text;

            std::replace(tmp.begin(), tmp.end(), '\t', ' ');
            std::replace(tmp.begin(), tmp.end(), '\n', ' ');
            
            for (int i = 0; i < (int)tmp.size(); i++)
            {
                chr = tmp[i];

                if (chr == SECTION_ASSIGNER)
                {
                    // Item is a section

                    if (cur_section == NULL)
                    {
                        cur_section = new section(item_name);
                    }
                    else
                    {
                        cur_section =
                            cur_section->add_sub_section(item_name);
                    }

                    sections.push_back(cur_section);

                    section_index = sections.size();

                    item_name = "";
                }
                else if (chr == VALUE_ASSIGNER)
                {
                    // Item is a value

                    if (cur_section == NULL)
                    {
                        assert::valid_format(
                            false, "", "value outside of section");
                    }

                    item_value = "";

                    while ((chr = tmp[i]) != VALUE_DELIMITER)
                    {
                        chr = tmp[i];

                        if (chr == VALUE_DELIMITER ||
                            chr == SECTION_ASSIGNER ||
                            chr == SECTION_DELIMITER)
                        {
                            assert::valid_format(
                                false, "", "malformed value declaration");
                        }

                        if (chr != VALUE_ASSIGNER)
                        {
                            item_value.append(string_t(1, chr));
                        }

                        i++;
                    }

                    cur_section->add_value(item_name, item_value);

                    item_name = "";
                }
                else if (chr == SECTION_DELIMITER)
                {
                    // Current section closed

                    if (section_index > 0)
                    {
                        section_index--;
                    }
                    else
                    {
                        assert::valid_format(
                            false, "", "unexpected end of section");
                    }

                    cur_section = sections[section_index];
                }
                else
                {
                    if (chr == VALUE_DELIMITER)
                    {
                        assert::valid_format(
                            false, "", "unexpected value delimiter");
                    }

                    // None of the above, must be the name of an item

                    item_name.append(string_t(1, chr));
                }
            }

            if (section_index != 0)
            {
                assert::valid_format(
                    false, "", "unclosed section");
            }
        }
        catch (const exception_t& exception)
        {
            if (sections.size() > 0)
            {
                // It is only required to delete the root section since all
                // sub-sections will be delete by it's destructor.

                safe_delete(sections.front());
            }
            
            throw runtime_error_t(exception.what());
        }

        return cur_section;

    } /* parse_section */

    /*---------------------------------------------------------------------- */

} /* hyenae */
