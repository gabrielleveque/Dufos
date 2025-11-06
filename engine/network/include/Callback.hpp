/*
** EPITECH PROJECT, 2025
** Dufos
** File description:
** Callback
*/

#pragma once

#include "Enum/Connection.hpp"
#include "Data/Message.hpp"

#include <functional>

namespace Engine::Network
{
    class Callback {
        public:
            /**
             * @enum Callback
             * @brief The different callback of the network module
             */
            enum class Type {
                ON_CONNECTION,
                ON_DISCONNECTION,
                ON_MESSAGE_RECEPTION
            };

            /**
             * @brief Handler of the callbacks for a new connection
             *
             * @param clientId The id of the connected client
             */
            void onConnection(std::uint32_t clientId);

            /**
             * @brief Set the callback for a client connection
             *
             * @param func The function to set
             */
            void setOnConnection(std::function<void(std::uint32_t)> func);

            /**
             * @brief Handler of the callbacks for a disconnection
             *
             * @param clientId The id of the disconnected client
             */
            void onDisconnection(std::uint32_t clientId);

            /**
             * @brief Set the callback for a client disconnection
             *
             * @param func The function to set
             */
            void setOnDisconnection(std::function<void(std::uint32_t)> func);

            /**
             * @brief Handler of the callbacks for a message reception
             *
             * @param type The type of the connection
             * @param clientId The id of the client
             * @param message The received message
             */
            void onMessageReception(Enum::Connection::Type type, std::uint32_t clientId, Data::Message& message);

            /**
             * @brief Set the callback for a message reception
             *
             * @param func The function to set
             */
            void setOnMessageReception(std::function<void(Enum::Connection::Type, std::uint32_t, Data::Message&)> func);

        private:
            std::function<void(std::uint32_t)> _onConnection;                                 /*!> The function to call when a clients connect (to be defined by the user) */
            std::function<void(std::uint32_t)> _onDisconnection;                              /*!> The function to call when a clients disconnect (to be defined by the user) */
            std::function<void(Enum::Connection::Type, std::uint32_t, Data::Message&)> _onMessageReception; /*!> The function to call when a message is received (to be defined by the user) */
    };
}
