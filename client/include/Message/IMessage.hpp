/*
** EPITECH PROJECT, 2025
** dufos
** File description:
** IMessage
*/

#pragma once

#include "NetworkManager.hpp"

#include <cstdint>

#include <set>

namespace Dufos
{
    class Client;

    namespace Message
    {
        class IMessage
        {
            public:
                /**
                 * @enum MessageType
                 * @brief The different message types
                 */
                enum class Type {
                    TO_EXECUTE,
                    TO_PROCESS
                };

                /**
                 * @brief Destroy the IMessage object
                 */
                virtual ~IMessage() = default;

                /**
                 * @brief Get the type of the message
                 *
                 * @return std::set<Type> The types of the message
                 */
                virtual std::set<Type> getType() const = 0;

                /**
                 * @brief Execute the message
                 *
                 * @param client The client instance
                 * @param id An id that will be treated by the message
                 * @return true if the message was sent successfully, false otherwise
                 */
                virtual bool execute(Client& client, std::uint32_t id = 0) = 0;

                /**
                 * @brief Process the message
                 *
                 * @param message The message received from the server
                 * @param client The client instance
                 * @param id An id that will be treated by the message
                 * @return true if the message was sent successfully, false otherwise
                 */
                virtual bool process(Network::Data::Message& message, Client& client, std::uint32_t id = 0) = 0;

            protected:
                /**
                 * @brief Set the Message Size object
                 *
                 * @param msg The message to fill with size data
                 */
                virtual void setMessageSize(std::vector<std::uint8_t>& msg, std::uint32_t size) = 0;
        };
    }
}
