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

#ifndef CONFIG_H
#define CONFIG_H

#include "common.h"

namespace hyenae
{
    /*---------------------------------------------------------------------- */

	class config
	{
        public:
            /* Delimiters */
            static const char VALUE_ASSIGNER = '=';
            static const char VALUE_DELIMITER = ';';
            static const char SECTION_ASSIGNER = '{';
            static const char SECTION_DELIMITER = '}';

            class value
            {
                private:
                    string_t _name;
                    string_t _value;

                public:
                    value(const string_t& name, const string_t& value = "");
                    string_t get_name() const;
                    string_t get_value() const;
                    void set_value(const string_t& value);
                    string_t to_string() const;

            }; /* value */

            class section
            {
                private:
                    string_t _name;
                    vector_t<value*> _values;
                    vector_t<section*> _sub_sections;

                public:
                    section(const string_t& name);
                    ~section();
                    string_t get_name() const;
                    size_t value_count() const;
                    size_t sub_section_count() const;
                    bool has_value(const string_t& name) const;
                    bool has_sub_section(const string_t& name) const;
                    value* value_at(const size_t pos) const;
                    section* sub_section_at(const size_t pos) const;
                    value* value_by_name(const string_t& name) const;
                    section* sub_section_by_name(const string_t& name) const;
                    config::section* add_sub_section(const string_t& name);
                    void remove_sub_section(const string_t& name);

                    config::value* add_value(
                        const string_t& name, const string_t& value = "");

                    void remove_value(const string_t& name);
                    string_t to_string() const;

                private:
                    value* value_by_name(
                        const string_t& name, bool throw_exception) const;

                    section* sub_section_by_name(
                        const string_t& name, bool throw_exception) const;

            }; /* section */

        private:
            section* _root_section;

            config(section* root_section);

        public:
            config(string_t name = "config");
            ~config();
            static config* parse(const string_t& text);
            section* get_root_section() const;
            string_t to_string();

	}; /* config */

    /*---------------------------------------------------------------------- */

} /* hyenae */

#endif /* CONFIG_H */
