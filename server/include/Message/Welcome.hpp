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
             * @param server The server instance
             * @param id An id that will be treated by the message
             * @return true if the message was sent successfully, false otherwise
             */
            bool execute(Server& server, std::uint32_t id);
    };
}
