#ifndef UDP_FRAME_GENERATOR_H
#define UDP_FRAME_GENERATOR_H

#include "address_generator.h"
#include "../integer_generator.h"
#include "../fixed_data_generator.h"
#include "../../data_transformation/to_network_order.h"
#include "../../data_transformation/to_tcp_udp_checksum.h"

namespace hyenae::model::generators::protocols
{
	/*---------------------------------------------------------------------- */

	class udp_frame_generator :
		public data_generator
	{
		private:
			using to_network_order_t =
				data_transformations::to_network_order;

			using to_tcp_udp_checksum_t =
				data_transformations::to_tcp_udp_checksum;

		private:
			integer_generator* _src_port = NULL;
			integer_generator* _dst_port = NULL;
			fixed_data_generator* _length = NULL;
			generator_group* _checksum = NULL;
			fixed_data_generator* _checksum_dummy = NULL;
			generator_group _payload;
			generator_group _packet;

		public:
			udp_frame_generator(
				data_generator* pseudo_header,
				const string_t& src_port_pattern = "****",
				size_t src_port_pattern_base = 10,
				const string_t& dst_port_pattern = "****",
				size_t dst_port_pattern_base = 10);

			~udp_frame_generator();
			void next(bool data_changed = true);
			void reset(bool data_changed = true);
			generator_group* get_payload();

		protected:
			size_t data_size() const;
			byte_t* data_to_buffer(byte_t* buffer, size_t size) const;

		private:
			void update_length();

	}; /* udp_frame_generator */

	/*---------------------------------------------------------------------- */

} /* hyenae::model::generators::protocols */

#endif /* UDP_FRAME_GENERATOR_H */
