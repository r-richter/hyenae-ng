#include "../../../include/assert.h"
#include "../../../include/model/data_transformation/to_tcp_udp_checksum.h"

#include <cstring>

namespace hyenae::model::data_transformations
{
	/*---------------------------------------------------------------------- */

	to_tcp_udp_checksum* to_tcp_udp_checksum::_instance = NULL;

	/*---------------------------------------------------------------------- */

	to_tcp_udp_checksum* to_tcp_udp_checksum::get_instance()
	{
		if (_instance == NULL)
		{
			_instance = new to_tcp_udp_checksum();
		}

		return _instance;

	} /* get_instance */

	/*---------------------------------------------------------------------- */

	size_t to_tcp_udp_checksum::result_size(size_t data_size) const
	{
		return sizeof(uint16_t);

	} /* result_size */

	/*---------------------------------------------------------------------- */

	byte_t* to_tcp_udp_checksum::transform(byte_t* data, size_t size) const
	{
		byte_t* result = NULL;
		size_t result_size = 0;
		uint16_t checksum = 0;

		assert::argument_not_null(data, "data");

		checksum = this->checksum(data, size);
		result_size = this->result_size(size);

		result = (byte_t*)malloc(result_size);
		memset(result, 0, result_size);
		memcpy(result, &checksum, result_size);

		free(data);

		return result;

	} /* transform */

	/*---------------------------------------------------------------------- */

	uint16_t to_tcp_udp_checksum::checksum(byte_t* data, size_t size) const
	{
		unsigned long sum = 0;
		int tmp_size = size;

		while (tmp_size > 1)
		{
			sum += *((uint16_t*) data++);
			tmp_size -= sizeof(uint16_t);
		}

		if (tmp_size)
		{
			sum += *(unsigned char*)data;
		}

		sum = (sum >> 16) + (sum & 0xffff);
		sum += (sum >> 16);

		return (uint16_t)(~sum);

	} /* checksum */

	/*---------------------------------------------------------------------- */

} /* hyenae::model::data_transformations */
