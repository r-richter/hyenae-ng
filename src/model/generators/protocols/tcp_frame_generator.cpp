#include "../../../../include/assert.h"
#include "../../../../include/model/generators/protocols/tcp_frame_generator.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    tcp_frame_generator::tcp_frame_generator(
        data_generator* pseudo_header,
        const string_t& src_port_pattern,
        size_t src_port_pattern_base,
        const string_t& dst_port_pattern,
        size_t dst_port_pattern_base,
        const string_t& seq_num_pattern,
        size_t seq_num_pattern_base,
        const string_t& ack_num_pattern,
        size_t ack_num_pattern_base,
        bool cwr_flag,
        bool ece_flag,
        bool urg_flag,
        bool ack_flag,
        bool psh_flag,
        bool rst_flag,
        bool syn_flag,
        bool fin_flag,
        const string_t& win_size_pattern,
        size_t win_size_pattern_base,
        const string_t& urg_pointer_pattern,
        size_t urg_pointer_pattern_base)
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

        // Sequence Number
        _seq_num = integer_generator::create_uint32(
            seq_num_pattern, seq_num_pattern_base);
        _seq_num->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_seq_num);

        // Acknowledgement Number
        _ack_num = integer_generator::create_uint32(
            ack_num_pattern, ack_num_pattern_base);
        _ack_num->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_ack_num);

        // Data Offset & Reserved
        _data_offset = fixed_data_generator::allocate_uint8();
        _data_offset->set_uint8(DATA_OFFSET);
        _packet.add_generator(_data_offset);

        // Flags
        _flags = fixed_data_generator::allocate_uint8();
        _flags->set_uint8(
            (cwr_flag << 7) +
            (ece_flag << 6) +
            (urg_flag << 5) +
            (ack_flag << 4) +
            (psh_flag << 3) +
            (rst_flag << 2) +
            (syn_flag << 1) +
            fin_flag);
        _packet.add_generator(_flags);

        // Window Size
        _win_size = integer_generator::create_uint16(
            win_size_pattern, win_size_pattern_base);
        _win_size->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_win_size);

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
        _checksum->add_generator(_seq_num);
        _checksum->add_generator(_ack_num);
        _checksum->add_generator(_data_offset);
        _checksum->add_generator(_flags);
        _checksum->add_generator(_win_size);
        _checksum->add_generator(_checksum_dummy);
        _checksum->add_generator(_urg_pointer);
        _checksum->add_generator(&_payload);

        // Urgent Pointer
        _urg_pointer = integer_generator::create_uint16(
            urg_pointer_pattern, urg_pointer_pattern_base);
        _urg_pointer->add_transformation(to_network_order_t::get_instance());
        _packet.add_generator(_urg_pointer);

        // Payload
        _packet.add_generator(&_payload);

    } /* tcp_frame_generator */

    /*---------------------------------------------------------------------- */

    tcp_frame_generator::~tcp_frame_generator()
    {
        safe_delete(_src_port);
        safe_delete(_dst_port);
        safe_delete(_seq_num);
        safe_delete(_ack_num);
        safe_delete(_data_offset);
        safe_delete(_flags);
        safe_delete(_win_size);
        safe_delete(_checksum);
        safe_delete(_urg_pointer);
        safe_delete(_checksum_dummy);

    } /* ~tcp_frame_generator */

    /*---------------------------------------------------------------------- */

    void tcp_frame_generator::next(bool data_changed)
    {
        _src_port->next(false);
        _dst_port->next(false);
        _seq_num->next(false);
        _ack_num->next(false);
        _win_size->next(false);
        _urg_pointer->next(false);
        _payload.next();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* next */

    /*---------------------------------------------------------------------- */

    void tcp_frame_generator::reset(bool data_changed)
    {
        _src_port->reset(false);
        _dst_port->reset(false);
        _seq_num->reset(false);
        _ack_num->reset(false);
        _win_size->reset(false);
        _urg_pointer->reset(false);
        _payload.reset();

        if (data_changed)
        {
            this->data_changed();
        }

    } /* reset */

    /*---------------------------------------------------------------------- */

    generator_group* tcp_frame_generator::get_payload()
    {
        return &_payload;

    } /* get_payload */

    /*---------------------------------------------------------------------- */

    size_t tcp_frame_generator::data_size() const
    {
        return _packet.size();

    } /* data_size */

    /*---------------------------------------------------------------------- */

    byte_t* tcp_frame_generator::data_to_buffer(
        byte_t* buffer, size_t size) const
    {
        return _packet.to_buffer(buffer, size);

    } /* data_to_buffer */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */
