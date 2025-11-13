
#pragma once

#include "Account.hpp"

#include <cstdint>
#include <string>

namespace Dufos
{
    class Client
    {
        public:
            /**
             * @brief Construct a new Client object
             */
            Client(std::string host, std::uint16_t port);

            /**
             * @brief Run the client main loop
             */
            void run();

        private:
            /**
             * @brief Setup the network callbacks
             */
            void setupCallbacks();

            /**
             * @brief Wait for the connection to be established
             */
            void waitForConnection();

            bool _connected; /*!< If the client is connected to the server */

            Account::Info _accountInfo; /*!< The account information of the client */
    };
}
