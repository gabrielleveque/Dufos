
#include "Message/Message.hpp"
#include "NetworkManager.hpp"
#include "Server.hpp"

#include <iostream>
#include <csignal>

volatile bool sigintCatch = false;

Dufos::Server::Server(std::string host, std::uint16_t port)
{
    Network::NetworkManager& manager = Network::NetworkManager::getInstance();

    manager.initialize(Network::Enum::Connection::Side::SERVER);
    manager.createConnection(Network::Enum::Connection::Type::TCP, {host, port});

    std::signal(SIGINT, [](int signal) {
        if (signal == SIGINT) {
            sigintCatch = true;
        }
    });

    setupCallbacks();
}

void Dufos::Server::setupCallbacks()
{
    Network::NetworkManager& manager = Network::NetworkManager::getInstance();

    manager.callbacks().setOnConnection([this](std::uint32_t clientId) {
        Message::Message::sendMessage(Message::Message::Name::WELCOME, *this, clientId);
    });

    manager.callbacks().setOnDisconnection([](std::uint32_t clientId) {
        std::cout << "Client disconnected: " << clientId << std::endl;
    });

    manager.callbacks().setOnMessageReception([](Network::Enum::Connection::Type type, std::uint32_t clientId, Network::Data::Message& message) {
        std::cout << "Message received from client " << clientId << " on connection type " << static_cast<int>(type) << " with opcode " << static_cast<int>(message.opcode) << std::endl;
    });
}

void Dufos::Server::run()
{
    while (!sigintCatch) {
        // Main server loop
    }
}
