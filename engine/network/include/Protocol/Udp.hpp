
#pragma once

#include "Enum/Connection.hpp"
#include "Data/Endpoint.hpp"
#include "Data/Message.hpp"
#include "Socket.hpp"

#include <cstdint>
#include <thread>

namespace Engine::Network::Protocol
{
    class Udp
    {
        public:
            /**
             * @brief Construct a new Udp object
             *
             * @param endpoint The endpoint on which to create the object
             */
            Udp(Data::Endpoint endpoint, Enum::Connection::Side side);

            /**
             * @brief Construct a new Udp object
             */
            Udp();

            /**
             * @brief Stop the udp instance
             */
            void stop();

            /**
             * @brief Main loop of the udp instance
             */
            void run();

            /**
             * @brief Read from the udp socket
             */
            void readFromSocket();

            /**
             * @brief Send a message to a given socket
             *
             * @param endpoint The endpoint where to send the message
             * @param msg The message to send
             */
            void sendToEndpoint(Data::Endpoint endpoint, std::vector<std::uint8_t>& msg);

        private:
            /**
             * @brief Read the header of the datagram issued to the server
             *
             * @param endpoint The endpoint to read from
             * @param datagram The datagram to store the information in
             * @return std::size_t The number of bytes read
             */
            std::size_t readDatagram(Socket::Address& addr, Socket::AddressLength& len, Data::Datagram& datagram);

            Enum::Connection::Side _side; /*!> The side of the connection (client or server) */
            bool _running;                /*!> If the tcp instance should run */

            Socket _socket;                       /*!> The udp socket */
            std::vector<Socket::PollFd> _pollFds; /*!> The pollfd array for the tcp instance */
    };
}
