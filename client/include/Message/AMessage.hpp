/*
** EPITECH PROJECT, 2025
** dufos
** File description:
** AMessage
*/

#pragma once

#include "Message/IMessage.hpp"

namespace Dufos::Message
{
    class AMessage : public IMessage
    {
        public:
            /**
             * @brief Construct a new AMessage object
             */
            AMessage() = default;

            /**
             * @brief Destroy the AMessage object
             */
            ~AMessage() = default;

            /**
             * @brief Get the type of the message
             *
             * @return MessageType The type of the message
             */
            Type getType() const;

            /**
             * @brief Execute the message
             *
             * @param client The client instance
             * @param id An id that will be treated by the message
             * @return true if the message was sent successfully, false otherwise
             */
            virtual bool execute(Client& client, std::uint32_t id = 0);
            /**
             * @brief Process the message
             *
             * @param message The message received from the server
             * @param client The client instance
             * @param id An id that will be treated by the message
             * @return true if the message was processed successfully, false otherwise
             */
            virtual bool process(Network::Data::Message& message, Client& client, std::uint32_t id = 0);

        protected:
            /**
             * @brief Set the Message Size object
             *
             * @param msg The message to fill with size data
             */
            void setMessageSize(std::vector<std::uint8_t>& msg, std::uint32_t size);

            Type _type; /*!> The type of the message (to execute or to process) */
    };
}
