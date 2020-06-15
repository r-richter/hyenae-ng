/*
 * Hyenae NG
 *   Advanced Network Packet Generator (NextGen)
 *
 * Copyright (C) 2020 Robin Richter
 *
 *   Contact  : richterr@users.sourceforge.net
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
#include "../../../include/model/outputs/network_output.h"

namespace hyenae::model::outputs
{
    /*---------------------------------------------------------------------- */

    network_output::network_output(device* device)
    {
        assert::argument_not_null((void*)device, "device");

        _device = device;

    } /* network_output */

    /*---------------------------------------------------------------------- */

    network_output::~network_output()
    {
        close();

    } /* ~network_output */

    /*---------------------------------------------------------------------- */

    void network_output::list_devices(vector_t<device*>& result)
    {
        pcap_if_t* devices = NULL;
        char error[PCAP_ERRBUF_SIZE];
        
        result.clear();

        if (pcap_findalldevs(&devices, error) == -1)
        {
            assert::legal_state(
                false, "", "Failed to lookup network devices");
        }

        for (pcap_if_t* dev = devices; dev != NULL; dev = dev->next)
        {
            result.push_back(new device(dev->name, dev->description));
        }

        if (devices != NULL)
        {
            pcap_freealldevs(devices);
        }
        
    } /* list_devices */

    /*---------------------------------------------------------------------- */

    void network_output::open()
    {
        char error[PCAP_ERRBUF_SIZE];

        assert::legal_call(_pcap == NULL, "", "already open");
        
        _pcap = pcap_open_live(
            _device->get_name().c_str(), BUFSIZ, 0, 0, error);

        assert::legal_state(
            _pcap != NULL, "", "Failed to open network device");

    } /* open */

    /*---------------------------------------------------------------------- */

    void network_output::close() noexcept
    {
        if (_pcap != NULL)
        {
            pcap_close(_pcap);

            // No delete required since pcap_close()
            // deallocates the pointer.

            _pcap = NULL;
        }

    } /* close */

    /*---------------------------------------------------------------------- */

    void network_output::send(byte_t* data, size_t size)
    {
        int result = 0;

        assert::legal_call(_pcap != NULL, "", "not open");
        assert::argument_not_null(data, "data");
        assert::in_range(size > 0, "size");

        result = pcap_sendpacket(_pcap, (unsigned char*)data, size);

        assert::legal_state(result == 0, "", "Failed to write to network");
        
    } /* send */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::outputs */
