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

namespace hyenae
{
    /*---------------------------------------------------------------------- */

    config::section::section(const string_t& name)
    {
        _name = name;

    } /* section */

    /*---------------------------------------------------------------------- */

    config::section::~section()
    {
        for (auto section : _sub_sections)
        {
            delete section;
        }

        for (auto value : _values)
        {
            delete value;
        }

    } /* ~section */
    
    /*---------------------------------------------------------------------- */

    string_t config::section::get_name() const
    {
        return _name;

    } /* section */

    /*---------------------------------------------------------------------- */

    size_t config::section::value_count() const
    {
        return _values.size();

    } /* value_count */

    /*---------------------------------------------------------------------- */

    size_t config::section::sub_section_count() const
    {
        return _sub_sections.size();

    } /* sub_section_count */

    /*---------------------------------------------------------------------- */

    bool config::section::has_value(const string_t& name) const
    {
        return value_by_name(name, false) != NULL;

    } /* has_value */

    /*---------------------------------------------------------------------- */

    bool config::section::has_sub_section(const string_t& name) const
    {
        return sub_section_by_name(name, false);

    } /* has_sub_section */

    /*---------------------------------------------------------------------- */

    config::value* config::section::value_at(const size_t pos) const
    {
        return _values.at(pos);

    } /* value_at */

    /*---------------------------------------------------------------------- */

    config::section* config::section::sub_section_at(const size_t pos) const
    {
        return _sub_sections.at(pos);
       
    } /* sub_section_at */

    /*---------------------------------------------------------------------- */

    config::value* config::section::value_by_name(const string_t& name) const
    {
        return value_by_name(name, true);
    }

    /*---------------------------------------------------------------------- */

    config::section* config::section::sub_section_by_name(
        const string_t& name) const
    {
        return sub_section_by_name(name, true);
    }

    /*---------------------------------------------------------------------- */

    config::section* config::section::add_sub_section(const string_t& name)
    {
        section* new_section = NULL;

        if (has_sub_section(name))
        {
            assert::legal_call(false, "", "section already exists");
        }

        new_section = new section(name);

        _sub_sections.push_back(new_section);

        return new_section;

    } /* add_sub_section */

    /*---------------------------------------------------------------------- */

    void config::section::remove_sub_section(const string_t& name)
    {
        section* sub_section = NULL;

        if ((sub_section == sub_section_by_name(name, false)))
        {
            assert::legal_call(false, "", "section not found");
        }

        _sub_sections.erase(
            std::remove(_sub_sections.begin(), _sub_sections.end(), sub_section),
            _sub_sections.end());

        delete sub_section;

    } /* remove_sub_section */

    /*---------------------------------------------------------------------- */

    config::value* config::section::add_value(
        const string_t& name, const string_t& value)
    {
        config::value* new_value = NULL;

        if (has_value(name))
        {
            assert::legal_call(false, "", "value already exists");
        }
        new_value = new config::value(name, value);

        _values.push_back(new_value);

        return new_value;

    } /* add_sub_section */

    /*---------------------------------------------------------------------- */

    void config::section::remove_value(const string_t& name)
    {
        value* value = NULL;

        if ((value == value_by_name(name, false)))
        {
            assert::legal_call(false, "", "value not found");
        }

        _values.erase(
            std::remove(_values.begin(), _values.end(), value),
            _values.end());

        delete value;

    } /* remove_sub_section */

    /*---------------------------------------------------------------------- */

    string_t config::section::to_string() const
    {
        string_t section = "";

        section.append(_name);
        section.push_back(config::SECTION_ASSIGNER);
        
        for (auto value : _values)
        {
            section.append(value->to_string());
        }

        for (auto sub_section : _sub_sections)
        {
            section.append(sub_section->to_string());
        }

        section.push_back(config::SECTION_DELIMITER);

        return section;

    } /* to_string */

    /*---------------------------------------------------------------------- */

    config::value* config::section::value_by_name(
        const string_t& name, bool throw_exception) const
    {
        for (auto value : _values)
        {
            if (value->get_name() == name)
            {
                return value;
            }
        }

        if (throw_exception)
        {
            assert::legal_call(false, "", "value not found");
        }

        return NULL;
    }

    /*---------------------------------------------------------------------- */

    config::section* config::section::sub_section_by_name(
        const string_t& name, bool throw_exception) const
    {
        for (auto section : _sub_sections)
        {
            if (section->get_name() == name)
            {
                return section;
            }
        }

        if (throw_exception)
        {
            assert::legal_call(false, "", "section not found");
        }

        return NULL;
    }

    /*---------------------------------------------------------------------- */

} /* hyenae */
