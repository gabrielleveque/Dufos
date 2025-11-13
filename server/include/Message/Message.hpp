/*
** EPITECH PROJECT, 2025
** dufos
** File description:
** Message
*/

#pragma once

#include "Message/IMessage.hpp"

#include <unordered_map>
#include <memory>

namespace Dufos::Message
{
    class Message
    {
        public:
            /**
             * @enum Name
             * @brief The different message names
             */
            enum class Name {
                WELCOME = 1,
            };

            /**
             * @brief Send a message to a client
             *
             * @param name The name of the message to send
             * @param server The server instance
             * @param id An id that will be treated by the message
             * @return true if the message was sent successfully, false otherwise
             */
            static bool sendMessage(Name name, Server& server, std::uint32_t id = 0);

            /**
             * @brief Handle a received message from a client
             *
             * @param message The message received from the client
             * @param server The server instance
             * @param id An id that will be treated by the message
             * @return true if the message was processed successfully, false otherwise
             */
            static bool recvMessage(Network::Data::Message& message, Server& server, std::uint32_t id);

        private:
            static std::unordered_map<Name, std::shared_ptr<IMessage>> _messages; /*!< map of message names to their implementations */
    };
}
