#ifndef TCP_FRAME_GENERATOR_H
#define TCP_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../integer_generator.h"
#include "../fixed_data_generator.h"
#include "../../data_transformation/to_network_order.h"
#include "../../data_transformation/to_tcp_udp_checksum.h"

namespace hyenae::model::generators::protocols
{
    /*---------------------------------------------------------------------- */

    class tcp_frame_generator :
        public data_generator
    {
        private:
            using to_network_order_t =
                data_transformations::to_network_order;

            using to_tcp_udp_checksum_t =
                data_transformations::to_tcp_udp_checksum;

        private:
            static const uint8_t DATA_OFFSET = 5 << 3;

            integer_generator* _src_port = NULL;
            integer_generator* _dst_port = NULL;
            integer_generator* _seq_num = NULL;
            integer_generator* _ack_num = NULL;
            fixed_data_generator* _data_offset = NULL;
            fixed_data_generator* _flags = NULL;
            generator_group* _checksum = NULL;
            integer_generator* _win_size = NULL;
            integer_generator* _urg_pointer = NULL;
            fixed_data_generator* _checksum_dummy = NULL;
            generator_group _payload;
            generator_group _packet;

        public:
            tcp_frame_generator(
                data_generator* pseudo_header,
                const string_t& src_port_pattern = "****",
                size_t src_port_pattern_base = 10,
                const string_t& dst_port_pattern = "****",
                size_t dst_port_pattern_base = 10,
                const string_t& seq_num_pattern = "*****",
                size_t seq_num_pattern_base = 10,
                const string_t& ack_num_pattern = "*****",
                size_t ack_num_pattern_base = 10,
                bool cwr_flag = false,
                bool ece_flag = false,
                bool urg_flag = false,
                bool ack_flag = false,
                bool psh_flag = false,
                bool rst_flag = false,
                bool syn_flag = false,
                bool fin_flag = false,
                const string_t& win_size_pattern = "*****",
                size_t win_size_pattern_base = 10,
                const string_t& urg_pointer_pattern = "*****",
                size_t urg_pointer_pattern_base = 10);

            ~tcp_frame_generator();
            void next(bool data_changed = true);
            void reset(bool data_changed = true);
            generator_group* get_payload();

        protected:
            size_t data_size() const;
            byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

    }; /* tcp_frame_generator */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* TCP_FRAME_GENERATOR_H */
