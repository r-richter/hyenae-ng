#include "../../../../include/assert.h"
#include "../../../../include/model/generators/protocols/udp_frame_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    udp_frame_generator::udp_frame_generator(
        data_generator* pseudo_header,
        const string_t& src_port_pattern,
        size_t src_port_pattern_base,
        const string_t& dst_port_pattern,
        size_t dst_port_pattern_base)
    {
        assert::argument_not_null(pseudo_header, "pseudo_header");

        // Source Port
        _src_port = integer_generator::create_uint16(
            src_port_pattern, src_port_pattern_base);
        _src_port->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_src_port);

        // Destination Port
        _dst_port = integer_generator::create_uint16(
            dst_port_pattern, dst_port_pattern_base);
        _dst_port->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_dst_port);

        // Length
        _length = fixed_data_generator::allocate_uint16();
        _length->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_length);
        
        // Checksum
        //
        // Network order transformation does not have to be applied to the
        // checksum since the checksum itself is computed over the already
        // transformed data fields.
        _checksum = new generator_group();
        _checksum->add_transformation(to_tcp_udp_checksum_t::get_instance());
        _packet.add_generator(_checksum);

        // Checksum targets

        _checksum_dummy = fixed_data_generator::allocate_uint16();
        _checksum->add_generator(pseudo_header);
        _checksum->add_generator(_src_port);
        _checksum->add_generator(_dst_port);
        _checksum->add_generator(_length);
        _checksum->add_generator(_checksum_dummy);
        _checksum->add_generator(&_payload);

        // Payload
        _packet.add_generator(&_payload);

        // Update fields
        update_length();

    } /* udp_frame_generator */

    /*---------------------------------------------------------------------- */

    udp_frame_generator::~udp_frame_generator()
    {
        safe_delete(_src_port);
        safe_delete(_dst_port);
        safe_delete(_length);
        safe_delete(_checksum);
        safe_delete(_checksum_dummy);

    } /* ~udp_frame_generator */

    /*---------------------------------------------------------------------- */

    void udp_frame_generator::next(bool data_changed)
    {
        _src_port->next(false);
        _dst_port->next(false);
        _payload.next();

        update_length();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void udp_frame_generator::reset(bool data_changed)
    {
        _src_port->reset(false);
        _dst_port->reset(false);
        _payload.reset();

        update_length();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* udp_frame_generator::get_payload()
    {
        return &_payload;

    } /* get_payload */

    /*---------------------------------------------------------------------- */

    size_t udp_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* udp_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

    void udp_frame_generator::update_length()
    {
        _length->set_uint16((uint16_t)(8 + _payload.size()));

    } /* update_length */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
