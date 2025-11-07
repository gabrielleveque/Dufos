
#pragma once

#include <cstdint>
#include <vector>

namespace Engine::Network::Data
{
    /**
     * @struct Message
     * @brief The struct that will contains the information about a message
     */
    typedef struct {
        std::uint8_t opcode; /*!> The command issued */
        std::uint32_t length; /*!> The size of the data */
        std::vector<std::uint8_t> payload; /*!> The body of the command */
    } Message, Segment, Datagram;
}
