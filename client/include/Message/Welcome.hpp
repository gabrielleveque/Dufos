/*
** EPITECH PROJECT, 2025
** dufos
** File description:
** Welcome
*/

#pragma once

#include "Message/AMessage.hpp"

namespace Dufos::Message
{
    class Welcome : public AMessage
    {
        public:
            /**
             * @brief Construct a new Welcome object
             */
            Welcome();

            /**
             * @brief Execute the welcome message
             *
             * @param message The message received from the server
             * @param client The client instance
             * @param id An id that will be treated by the message
             * @return true if the message was sent successfully, false otherwise
             */
            bool process(Network::Data::Message& message, Client& client, std::uint32_t id);
    };
}
