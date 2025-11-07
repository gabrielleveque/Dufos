
#include "Callback.hpp"

void Engine::Network::Callback::onConnection(std::uint32_t clientId)
{
    if (_onConnection) {
        _onConnection(clientId);
    }
}

void Engine::Network::Callback::setOnConnection(std::function<void(std::uint32_t)> func)
{
    _onConnection = func;
}

void Engine::Network::Callback::onDisconnection(std::uint32_t clientId)
{
    if (_onDisconnection) {
        _onDisconnection(clientId);
    }
}

void Engine::Network::Callback::setOnDisconnection(std::function<void(std::uint32_t)> func)
{
    _onDisconnection = func;
}

void Engine::Network::Callback::onMessageReception(Enum::Connection::Type type, std::uint32_t clientId, Data::Message& message)
{
    if (_onMessageReception) {
        _onMessageReception(type, clientId, message);
    }
}

void Engine::Network::Callback::setOnMessageReception(std::function<void(Enum::Connection::Type, std::uint32_t, Data::Message&)> func)
{
    _onMessageReception = func;
}
