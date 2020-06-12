#ifndef TO_TCP_CHECKSUM_H
#define TO_TCP_CHECKSUM_H

#include "../data_transformation.h"

namespace hyenae::model::data_transformations
{
    /*---------------------------------------------------------------------- */

    class to_tcp_udp_checksum :
        public data_transformation
    {
    private:
        static to_tcp_udp_checksum* _instance;

    public:
        static to_tcp_udp_checksum* get_instance();
        size_t result_size(size_t data_size) const;
        byte_t* transform(byte_t* data, size_t size) const;

    private:
        uint16_t checksum(byte_t* data, size_t size) const;

    }; /* to_tcp_udp_checksum */

    /*---------------------------------------------------------------------- */

} /* hyenae::model::data_transformations */

#endif /* TO_TCP_CHECKSUM_H */
