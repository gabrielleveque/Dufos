
#pragma once

#include "Enum/Connection.hpp"
#include "Protocol/Tcp.hpp"
#include "Protocol/Udp.hpp"
#include "Singleton.hpp"
#include "Callback.hpp"

#include <unordered_map>
#include <functional>
#include <cstdint>
#include <memory>
#include <thread>
#include <vector>
#include <queue>

#define LOCALHOST "127.0.0.1"

namespace Network
{
    class NetworkManager : public Common::Singleton<NetworkManager>
    {
        public:
            /**
             * @brief Construct a new Network Manager object
             */
            NetworkManager();

            /**
             * @brief Destroy the Network Manager object
             */
            ~NetworkManager();

            /**
             * @brief Initialize the NetworkManager
             *
             * @param side The side of the connection (client or server)
             */
            void initialize(Enum::Connection::Side side);

            /**
             * @brief Stop the NetworkManager
             */
            void stop();

            /**
             * @brief Create a Connection object
             *
             * @param type The type of connection to create
             * @param endpoint The endpoint on which to create the connection
             */
            void createConnection(Enum::Connection::Type type, Data::Endpoint endpoint = Data::Endpoint{"", 0});

            /**
             * @brief Connect to the server (only for client side)
             */
            void connectToServer();

            /**
             * @brief Send a message to the server
             *
             * @param type The type of the connection on which to send the message
             * @param msg The message to send
             */
            void sendMessage(Enum::Connection::Type type, std::vector<std::uint8_t> msg);

            /**
             * @brief Send a message to a client
             *
             * @param type The type of the connection on which to send the message
             * @param ids The ids of the clients to which to send the message
             * @param msg The message to send
             */
            void sendMessageTo(Enum::Connection::Type type, std::vector<std::uint32_t> ids, std::vector<std::uint8_t> msg);

            /**
             * @brief Handler of the callbacks
             *
             * @param callback The type of the callback
             * @param socket The socket of the client
             */
            void callbackHandler(Callback::Type callback, Socket& socket);

            /**
             * @brief Handler of the callbacks
             *
             * @param callback The type of the callback
             * @param id The id of the client
             */
            void callbackHandler(Callback::Type callback, std::uint32_t id);

            /**
             * @brief Handler of the callbacks
             *
             * @param callback The type of the callback
             * @param type The type of the connection
             * @param id The id of the client
             * @param message The received message
             */
            void callbackHandler(Callback::Type callback, Enum::Connection::Type type, std::uint32_t id, Data::Message& message);

            /**
             * @brief Get the Client Socket By object
             *
             * @tparam T The type of the reference
             * @param ref The reference to the object
             * @return Socket& The socket of the client corresponding to the given object
             */
            template <typename T>
            Socket& getClientSocketBy(T& ref);

            /**
             * @brief Get the Client Id By object
             *
             * @tparam T The type of the reference
             * @param ref The reference to the object
             * @return std::uint32_t The id of the client corresponding to the given object
             */
            template <typename T>
            std::uint32_t getClientIdBy(T& ref);

            /**
             * @brief Set the server endpoint (only for client side)
             *
             * @param endpoint The endpoint of the server
             */
            void setServerEndpoint(Data::Endpoint endpoint);

            /**
             * @brief Get the Callback Handler object
             *
             * @return Callback& The callback handler
             */
            Callback& callbacks();

        private:
            /**
             * @struct Server
             * @brief Represent the server information
             */
            struct Server {
                    std::unordered_map<std::uint32_t, std::shared_ptr<Socket>> clients; /*!> The map of the clients connected via the tcp socket */
                    std::uint32_t nextClientId;                                         /*!> The next id to give to a client */
            };

            /**
             * @struct Client
             * @brief Represent the client information
             */
            struct Client {
                    Data::Endpoint server;          /*!> The endpoint of the server */
                    std::shared_ptr<Socket> socket; /*!> The client connection information */
                    std::uint32_t clientPort;       /*!> The port of the client */
            };

            /**
             * @brief The main loop of the NetworkManager
             */
            void run();

            /**
             * @brief Get an available port for the client (only for client side)
             */
            std::uint16_t getAvailablePort();

            friend class Singleton<NetworkManager>; /*!> Friend class to allow access to the private constructor and destructor */

            bool _running;                /*!> If the NetworkManager is running */
            std::thread _mainThread;      /*!> The main thread of the NetworkManager */
            Enum::Connection::Side _side; /*!> The side of the connection (client or server) */

            Server _server; /*!> The server information (only for server side) */
            Client _client; /*!> The client information (only for client side) */

            std::shared_ptr<Protocol::Tcp> _tcp; /*!> The tcp instance */
            std::thread _tcpThread;              /*!> The tcp thread */
            std::shared_ptr<Protocol::Udp> _udp; /*!> The udp instance */
            std::thread _udpThread;              /*!> The udp thread */

            Callback _callbacks; /*!> The callback handler */

            std::queue<std::uint16_t> _disconnectionQueue; /*!> The queue of disconnections to process */
    };
}
