#include "engine/network/include/NetworkManager.hpp"

#include <iostream>
#include <csignal>

volatile bool sigintCatch = false;

int main(void)
{
    Engine::Network::NetworkManager& manager = Engine::Network::NetworkManager::getInstance();

    manager.initialize(Engine::Network::Enum::Connection::Side::SERVER);
    manager.createConnection(Engine::Network::Enum::Connection::Type::TCP, {LOCALHOST, 8080});

    std::signal(SIGINT, [](int signal) {
        if (signal == SIGINT) {
            sigintCatch = true;
        }
    });

    manager.callbacks().setOnConnection([](std::uint32_t clientId) {
        std::cout << "Client connected: " << clientId << std::endl;
    });

    manager.callbacks().setOnDisconnection([](std::uint32_t clientId) {
        std::cout << "Client disconnected: " << clientId << std::endl;
    });

    while (!sigintCatch) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
