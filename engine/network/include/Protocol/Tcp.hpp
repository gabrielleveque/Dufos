
#pragma once

#include "Enum/Connection.hpp"
#include "Data/Endpoint.hpp"
#include "Data/Message.hpp"
#include "Socket.hpp"

#include <cstdint>

namespace Engine::Network::Protocol
{
    class Tcp
    {
        public:
            /**
             * @brief Construct a new Tcp object
             *
             * @param endpoint The endpoint on which to create the object
             * @param type The side of the connection (client or server)
             */
            Tcp(Data::Endpoint endpoint, Enum::Connection::Side side);

            /**
             * @brief Stop the tcp instance
             */
            void stop();

            /**
             * @brief Main loop of the tcp instance
             */
            void run();

            /**
             * @brief Connect to a server
             *
             * @param host The host to connect to
             * @param port The port to connect to
             */
            void connectToServer(const std::string& host, std::uint16_t port);

            /**
             * @brief Send a message to a given socket
             *
             * @param socket The socket to send the message
             * @param id The id of the client (for disconnection purpose)
             * @param msg The message to send
             */
            void sendToSocket(Socket& socket, std::vector<std::uint8_t>& msg);

        private:
            Enum::Connection::Side _side; /*!> The side of the connection (client or server) */
            bool _running;        /*!> If the tcp instance should run */

            Socket _socket;                       /*!> The tcp instance socket */
            std::vector<Socket::PollFd> _pollFds; /*!> The pollfd array for the tcp instance */

            /**
             * @brief Accept a socket on the tcp instance
             */
            void acceptSocket();

            /**
             * @brief Disconnect a socket from the tcp instance
             */
            void disconnectSocket(std::size_t id);

            /**
             * @brief Read the header of the segment issued to the server
             *
             * @param socket The socket to read on
             * @param segment The segment to store the information in
             * @return std::size_t The number of bytes read
             */
            std::size_t readHeader(Socket& socket, Data::Segment& segment);

            /**
             * @brief Read the body of the segment issued to the server
             *
             * @param socket The socket to read on
             * @param segment The segment to store the information in
             * @return std::size_t The number of bytes read
             */
            std::size_t readBody(Socket& socket, Data::Segment& segment);

            /**
             * @brief Read from a given socket
             *
             * @param socket The socket to read from
             * @param id The id of the client (for disconnection purpose)
             */
            bool readFromSocket(Socket& socket);
    };
}
