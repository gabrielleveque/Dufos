
#include "NetworkManager.hpp"
#include "Utils.hpp"

#include <type_traits>

Network::NetworkManager::NetworkManager() : _running(true)
{
    Socket::startup();
}

Network::NetworkManager::~NetworkManager()
{
    _running = false;
    if (_tcp) {
        _tcp->stop();
    }
    Common::Utils::joinThread(_tcpThread);
    if (_udp) {
        _udp->stop();
    }
    Common::Utils::joinThread(_udpThread);
    Common::Utils::joinThread(_mainThread);
    Socket::cleanup();
}

void Network::NetworkManager::initialize(Enum::Connection::Side side)
{
    if (side == Enum::Connection::Side::CLIENT) {
        _client.clientPort = getAvailablePort();
    }
    if (side == Enum::Connection::Side::SERVER) {
        _server.nextClientId = 1;
    }
    _side = side;
    _mainThread = std::thread(&NetworkManager::run, this);
}

void Network::NetworkManager::stop()
{
    _running = false;
}

void Network::NetworkManager::run()
{
    while (_running) {
        while (!_disconnectionQueue.empty()) {
            if (_side == Enum::Connection::Side::SERVER) {
                std::uint32_t id = _disconnectionQueue.front();

                if (_server.clients.find(id) == _server.clients.end()) {
                    return;
                }
                _callbacks.onDisconnection(id);
                _server.clients.erase(id);
            }
            _disconnectionQueue.pop();
        }
    }
}

void Network::NetworkManager::createConnection(Enum::Connection::Type type, Data::Endpoint endpoint)
{
    if (_side == Enum::Connection::Side::CLIENT) {
        endpoint.port = _client.clientPort;
    }
    switch (type) {
        case Enum::Connection::Type::TCP:
            _tcp = std::make_shared<Protocol::Tcp>(endpoint, _side);
            if (_side == Enum::Connection::Side::SERVER) {
                _tcpThread = std::thread(&Protocol::Tcp::run, _tcp);
            }
            break;
        case Enum::Connection::Type::UDP:
            _udp = std::make_shared<Protocol::Udp>(endpoint, _side);
            _udpThread = std::thread(&Protocol::Udp::run, _udp);
            break;
        default:
            break;
    }
}

void Network::NetworkManager::connectToServer()
{
    if (_side == Enum::Connection::Side::CLIENT && _tcp) {
        _tcp->connectToServer(_client.server.address, _client.server.port);
        _tcpThread = std::thread(&Protocol::Tcp::run, _tcp);
    }
}

void Network::NetworkManager::sendMessage(Enum::Connection::Type type, std::vector<std::uint8_t> msg)
{
    if (_side != Enum::Connection::Side::CLIENT) {
        return;
    }
    switch (type) {
        case Enum::Connection::Type::TCP:
            _tcp->sendToSocket(*_client.socket, msg);
            break;
        case Enum::Connection::Type::UDP:
            _udp->sendToEndpoint(_client.server, msg);
            break;
        default:
            break;
    }
}

void Network::NetworkManager::sendMessageTo(Enum::Connection::Type type, std::vector<std::uint32_t> ids, std::vector<std::uint8_t> msg)
{
    if (_side != Enum::Connection::Side::SERVER || ids.empty()) {
        return;
    }
    for (std::uint32_t id : ids) {
        if (_server.clients.find(id) == _server.clients.end()) {
            return;
        }
        switch (type) {
            case Enum::Connection::Type::TCP:
                _tcp->sendToSocket(*_server.clients[id], msg);
                break;
            case Enum::Connection::Type::UDP:
                if (!_server.clients[id]) {
                    return;
                }
                _udp->sendToEndpoint(_server.clients[id]->getEndpoint(), msg);
                break;
            default:
                break;
        }
    }
}

void Network::NetworkManager::callbackHandler(Callback::Type callback, Socket& socket)
{
    if (callback == Callback::Type::ON_CONNECTION) {
        std::shared_ptr<Socket> connectionSocket = std::make_shared<Socket>(socket);

        if (_side == Enum::Connection::Side::CLIENT) {
            _client.socket = connectionSocket;
            _callbacks.onConnection(0);
        } else if (_side == Enum::Connection::Side::SERVER) {
            _server.clients[_server.nextClientId] = connectionSocket;
            _callbacks.onConnection(_server.nextClientId);
            _server.nextClientId++;
        }
    }
}

void Network::NetworkManager::callbackHandler(Callback::Type callback, std::uint32_t id)
{
    if (callback == Callback::Type::ON_DISCONNECTION) {
        _disconnectionQueue.push(id);
    }
}

void Network::NetworkManager::callbackHandler(Callback::Type callback, Enum::Connection::Type type, std::uint32_t id, Data::Message& message)
{
    if (callback == Callback::Type::ON_MESSAGE_RECEPTION) {
        if (_side != Enum::Connection::Side::CLIENT && _server.clients.find(id) == _server.clients.end()) {
            return;
        }
        _callbacks.onMessageReception(type, id, message);
    }
}

template <typename T>
Network::Socket& Network::NetworkManager::getClientSocketBy(T& ref)
{
    if (_side == Enum::Connection::Side::CLIENT) {
        throw std::runtime_error("Client side has no clients");
    }
    if (std::is_same_v<T, Socket::Fd>) {
        for (auto& [id, client] : _server.clients) {
            if (client && client->getFd() == ref) {
                return *client;
            }
        }
    }
    throw std::runtime_error("Client not found");
}

template Network::Socket& Network::NetworkManager::getClientSocketBy<Network::Socket::Fd>(Network::Socket::Fd& ref);

template <typename T>
std::uint32_t Network::NetworkManager::getClientIdBy(T& ref)
{
    if (_side == Enum::Connection::Side::CLIENT) {
        return 0;
    }
    if constexpr (std::is_same_v<T, Socket>) {
        for (auto& [id, client] : _server.clients) {
            if (client && client->getFd() == ref.getFd()) {
                return id;
            }
        }
    } else if constexpr (std::is_same_v<T, Data::Endpoint>) {
        for (auto& [id, client] : _server.clients) {
            if (client && client->getEndpoint() == ref) {
                return id;
            }
        }
    }
    throw std::runtime_error("Client not found");
}

template std::uint32_t Network::NetworkManager::getClientIdBy<Network::Socket>(Network::Socket& ref);
template std::uint32_t Network::NetworkManager::getClientIdBy<Network::Data::Endpoint>(Network::Data::Endpoint& ref);

void Network::NetworkManager::setServerEndpoint(Data::Endpoint endpoint)
{
    _client.server = endpoint;
}

std::uint16_t Network::NetworkManager::getAvailablePort()
{
    Socket socket(Enum::Connection::Type::TCP, {LOCALHOST, 0});
    Data::Endpoint endpoint = socket.getEndpoint();
    Socket::Address_in addr = {0};
    Socket::AddressLength addrLen = 0;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = ::inet_addr(LOCALHOST);
    addrLen = sizeof(addr);
    socket.bind((Socket::Address&) addr, addrLen);
    socket.getSockName((Socket::Address&) addr, addrLen);
    return ntohs(addr.sin_port);
}

Network::Callback& Network::NetworkManager::callbacks()
{
    return _callbacks;
}
