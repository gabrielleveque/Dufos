/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Tcp.cpp
*/

#include "NetworkManager.hpp"
#include "Protocol/Tcp.hpp"
#include "Bytes.hpp"

#include <iostream>
#include <thread>

Engine::Network::Protocol::Tcp::Tcp(Data::Endpoint endpoint, Enum::Connection::Side side) : _side(side), _running(true), _socket(Enum::Connection::Type::TCP, endpoint)
{
    Socket::Address_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(endpoint.port);
    if (endpoint != Data::Endpoint{"", 0}) {
        _socket.reuse();
        _socket.bind((Socket::Address&) addr, sizeof(addr));
        if (_side == Enum::Connection::Side::SERVER) {
            _socket.listen();
        }
    }
    _pollFds.push_back({.fd = _socket.getFd(), .events = POLLIN, .revents = 0});
}

void Engine::Network::Protocol::Tcp::stop()
{
    _running = false;
}

void Engine::Network::Protocol::Tcp::run()
{
    try {
        NetworkManager& manager = NetworkManager::getInstance();

        while (_running) {
            std::int32_t result = _socket.poll(_pollFds, _pollFds.size(), 0);

            if (result > 0 && _pollFds.size() >= 1) {
                if (_pollFds[0].revents & POLLIN) {
                    if (_side == Enum::Connection::Side::SERVER) {
                        acceptSocket();
                    } else {
                        readFromSocket(_socket);
                    }
                }
                if (_side == Enum::Connection::Side::SERVER) {
                    for (std::size_t i = 1; i < _pollFds.size(); i++) {
                        if (_pollFds[i].revents & POLLHUP) {
                            disconnectSocket(i);
                            i--;
                            continue;
                        }
                        if (_pollFds[i].revents & POLLIN) {
                            if (!readFromSocket(manager.getClientSocketBy<Socket::Fd>(_pollFds[i].fd))) {
                                disconnectSocket(i);
                                i--;
                            }
                        }
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::Network::Protocol::Tcp::connectToServer(const std::string& host, std::uint16_t port)
{
    if (_side != Enum::Connection::Side::CLIENT) {
        return;
    }
    try {
        NetworkManager& manager = NetworkManager::getInstance();
        Socket::Address_in addr = {0};

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = Socket::inetAddr(host.c_str());
        _socket.connect((Socket::Address&) addr, sizeof(addr));
        manager.callbackHandler(Callback::Type::ON_CONNECTION, _socket);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::Network::Protocol::Tcp::acceptSocket()
{
    if (_side != Enum::Connection::Side::SERVER) {
        return;
    }
    try {
        NetworkManager& manager = NetworkManager::getInstance();
        Socket::Address addr = {0};
        Socket::AddressLength addrLen = sizeof(addr);
        Socket socket = _socket.accept(addr, addrLen);

        _pollFds.push_back({.fd = socket.getFd(), .events = POLLIN, .revents = 0});
        socket.setEndpoint({::inet_ntoa(((Socket::Address_in&) addr).sin_addr), ntohs(((Socket::Address_in&) addr).sin_port)});
        manager.callbackHandler(Callback::Type::ON_CONNECTION, socket);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::Network::Protocol::Tcp::disconnectSocket(std::size_t id)
{
    if (_side != Enum::Connection::Side::SERVER) {
        return;
    }
    try {
        NetworkManager& manager = NetworkManager::getInstance();
        Socket& socket = manager.getClientSocketBy<Socket::Fd>(_pollFds[id].fd);

        manager.callbackHandler(Callback::Type::ON_DISCONNECTION, manager.getClientIdBy<Socket>(socket));
        _pollFds.erase(_pollFds.begin() + id);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::size_t Engine::Network::Protocol::Tcp::readHeader(Socket& socket, Data::Segment& segment)
{
    std::vector<std::uint8_t> buffer(5);
    std::size_t bytesRead = socket.recv(buffer, 5, 0);

    if (bytesRead != 5) {
        return 0;
    }
    segment.opcode = buffer[0];
    segment.length = Bytes::bytesToNumber(std::vector(buffer.begin() + 1, buffer.end()), 4);
    return bytesRead;
}

std::size_t Engine::Network::Protocol::Tcp::readBody(Socket& socket, Data::Segment& segment)
{
    if (segment.length == 0) {
        return 0;
    }
    segment.payload.resize(segment.length);
    std::size_t bytesRead = socket.recv(segment.payload, segment.length, 0);

    if (bytesRead != segment.length) {
        return 0;
    }
    return bytesRead;
}

bool Engine::Network::Protocol::Tcp::readFromSocket(Socket& socket)
{
    if (!_running) {
        return false;
    }
    try {
        NetworkManager& manager = NetworkManager::getInstance();
        Data::Segment segment = {0};

        if (readHeader(socket, segment) == 0) {
            return false;
        }
        if (readBody(socket, segment) == 0 && segment.length != 0) {
            return false;
        }
        manager.callbackHandler(Callback::Type::ON_MESSAGE_RECEPTION, Enum::Connection::Type::TCP, manager.getClientIdBy<Socket>(socket), segment);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return true;
}

void Engine::Network::Protocol::Tcp::sendToSocket(Socket& socket, std::vector<std::uint8_t>& msg)
{
    try {
        socket.send(msg, msg.size(), 0);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
