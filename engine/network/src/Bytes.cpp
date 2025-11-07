
#include "Bytes.hpp"

std::vector<std::uint8_t> Engine::Network::Bytes::numberToBytes(const std::uint64_t number, std::uint8_t bytesToWrite)
{
    std::uint8_t shift = (bytesToWrite - 1) * 8;
    std::vector<std::uint8_t> buffer;

    for (std::uint8_t i = 0; i < bytesToWrite - 1; i++) {
        buffer.push_back(static_cast<std::uint8_t>((number >> shift) & 0xFF));
        shift -= 8;
    }
    buffer.push_back(static_cast<std::uint8_t>(number & 0xFF));
    return buffer;
}

std::uint64_t Engine::Network::Bytes::bytesToNumber(const std::vector<std::uint8_t> bytes, std::uint8_t bytesToRead)
{
    std::uint8_t shift = (bytesToRead - 1) * 8;
    std::uint64_t number = 0;

    for (std::uint8_t i = 0; i < bytesToRead - 1; i++) {
        number |= static_cast<std::uint8_t>(bytes[i]) << shift;
        shift -= 8;
    }
    number |= static_cast<std::uint8_t>(bytes[bytesToRead - 1]);
    return number;
}
