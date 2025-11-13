
#include "Message/Message.hpp"
#include "NetworkManager.hpp"
#include "Client.hpp"

#include <chrono>
#include <iostream>
#include <csignal>

volatile bool shouldLeave = false;

Dufos::Client::Client(std::string host, std::uint16_t port) : _connected(false)
{
    Network::NetworkManager& manager = Network::NetworkManager::getInstance();

    manager.initialize(Network::Enum::Connection::Side::CLIENT);
    manager.setServerEndpoint({host, port});
    manager.createConnection(Network::Enum::Connection::Type::TCP, {host, port});

    std::signal(SIGINT, [](int signal) {
        if (signal == SIGINT) {
            shouldLeave = true;
        }
    });

    setupCallbacks();

    manager.connectToServer();

    waitForConnection();

    std::optional<Account::Info> info = Account::connectTo();

    if (shouldLeave || !info.has_value()) {
        shouldLeave = true;
        return;
    }
    _accountInfo = info.value();
}

void Dufos::Client::setupCallbacks()
{
    Network::NetworkManager& manager = Network::NetworkManager::getInstance();

    manager.callbacks().setOnConnection([this](std::uint32_t clientId) {
        _connected = true;
    });

    manager.callbacks().setOnMessageReception([this](Network::Enum::Connection::Type type, std::uint32_t clientId, Network::Data::Message& message) {
        Message::Message::recvMessage(message, *this, clientId);
    });
}

void Dufos::Client::waitForConnection()
{
    std::uint8_t state = 0;
    std::chrono::steady_clock::time_point lastUpdate = std::chrono::steady_clock::now();

    std::cout << "\e[?25l" << std::flush; //* Hide cursor
    while (!_connected && !shouldLeave) {
        if (std::chrono::steady_clock::now() - lastUpdate >= std::chrono::milliseconds(500)) {
            state = (state + 1) % 4;
            lastUpdate = std::chrono::steady_clock::now();
        }
        std::cout << "\rConnecting" << std::string(state, '.') << std::string(3 - state, ' ') << std::flush;
    }
    std::cout << "\rConnected" << std::string(4, ' ');
    std::cout << "\e[?25h" << std::endl; //* Show cursor
}

void Dufos::Client::run()
{
    while (!shouldLeave) {
        // Main Client loop
    }
}
