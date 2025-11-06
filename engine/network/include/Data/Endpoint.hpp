/*
** EPITECH PROJECT, 2025
** Dufos
** File description:
** Endpoint
*/

#pragma once

#include <cstdint>
#include <string>

namespace Engine::Network::Data
{
    /**
     * @struct Endpoint
     * @brief Represent an endpoint with an address and a port
     */
    struct Endpoint {
        std::string address; /*!> The address of the endpoint */
        std::uint16_t port; /*!> The port of the endpoint */

        /**
         * @brief Equality operator for Endpoint
         *
         * @param other The other Endpoint to compare with
         * @return true if both Endpoints are equal, false otherwise
         */
        bool operator==(const Endpoint &other) const {
            return address == other.address && port == other.port;
        }
    };
}
