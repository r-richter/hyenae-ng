/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
 *   Homepage : http://sourceforge.net/projects/hyenae-ng/
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

#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include "../../../common.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    typedef struct octet
    {
        byte_t byte;

    } octet_t;

    typedef struct hextet
    {
        byte_t bytes[2];

    } hextet_t;

    typedef struct mac_address
    {
        octet_t octets[6];

    } mac_address_t;

    typedef struct ipv4_address
    {
        octet_t octets[4];

    } ipv4_address_t;

    typedef struct ipv6_address
    {
        hextet_t hextets[8];

    } ipv6_address_t;

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* PROTOCOLS_H */