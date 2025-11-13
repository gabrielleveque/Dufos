
#pragma once

#include <cstdint>
#include <string>

namespace Dufos
{
    class Server
    {
        public:
            /**
             * @brief Construct a new Server object
             */
            Server(std::string host, std::uint16_t port);

            /**
             * @brief Run the server main loop
             */
            void run();

        private:
            /**
             * @brief Setup the network callbacks
             */
            void setupCallbacks();
    };
}
