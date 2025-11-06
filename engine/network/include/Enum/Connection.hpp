/*
** EPITECH PROJECT, 2025
** Dufos
** File description:
** Connection
*/

#pragma once

namespace Engine::Network::Enum::Connection
{
    /**
     * @enum Connection types
     * @brief Connection types
     */
    enum class Type {
        TCP, /*!> TCP connection type */
        UDP, /*!> UDP connection type */
    };

    /**
     * @enum Connection sides
     * @brief Connection sides
     */
    enum class Side {
        CLIENT, /*!> Client side */
        SERVER, /*!> Server side */
    };
}
