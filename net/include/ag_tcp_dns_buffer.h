#pragma once


#include <vector>
#include <optional>
#include "common/defs.h"


namespace ag {

class tcp_dns_buffer {
public:
    tcp_dns_buffer() = default;
    ~tcp_dns_buffer() = default;

    /**
     * Store a chunk of data
     * @param data the data chunk
     * @return a part of the chunk remaining after the DNS packet
     */
    Uint8View store(Uint8View data);

    /**
     * Try to extract a packet from the buffer
     * @return some packet if it's complete
     */
    std::optional<std::vector<uint8_t>> extract_packet();

private:
    std::optional<size_t> total_length;
    std::vector<uint8_t> buffer;
};

}
