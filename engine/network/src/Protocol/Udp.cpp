
#include "NetworkManager.hpp"
#include "Protocol/Udp.hpp"
#include "Bytes.hpp"

#include <iostream>

Engine::Network::Protocol::Udp::Udp(Data::Endpoint endpoint, Enum::Connection::Side side) : _side(side), _running(true), _socket(Enum::Connection::Type::UDP, endpoint)
{
    Socket::Address_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(endpoint.port);
    if (endpoint != Data::Endpoint{"", 0}) {
        _socket.reuse();
        _socket.bind((Socket::Address&) addr, sizeof(addr));
    }
    _pollFds.push_back({.fd = _socket.getFd(), .events = POLLIN, .revents = 0});
}

void Engine::Network::Protocol::Udp::stop()
{
    _running = false;
}

void Engine::Network::Protocol::Udp::run()
{
    try {
        while (_running) {
            std::int32_t result = _socket.poll(_pollFds, _pollFds.size(), 0);

            if (result > 0 && _pollFds.size() >= 1) {
                if (_pollFds[0].revents & POLLIN) {
                    readFromSocket();
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::size_t Engine::Network::Protocol::Udp::readDatagram(Socket::Address& addr, Socket::AddressLength& len, Data::Datagram& datagram)
{
    std::vector<std::uint8_t> buffer(1024);
    std::size_t bytesRead = _socket.recvFrom(buffer, buffer.size(), 0, addr, len);

    if (bytesRead < 5) {
        return 0;
    }
    datagram.opcode = buffer[0];
    datagram.length = Bytes::bytesToNumber(std::vector(buffer.begin() + 1, buffer.end()), 4);
    datagram.payload = std::vector(buffer.begin() + 5, buffer.begin() + 5 + datagram.length);
    return bytesRead;
}

void Engine::Network::Protocol::Udp::readFromSocket()
{
    try {
        NetworkManager& manager = NetworkManager::getInstance();
        Socket::Address addr = {0};
        Socket::AddressLength len = sizeof(addr);
        Data::Endpoint endpoint = {.address = "", .port = 0};
        Data::Datagram datagram = {0};

        if (readDatagram(addr, len, datagram) == 0) {
            return;
        }
        endpoint.address = ::inet_ntoa(((Socket::Address_in&) addr).sin_addr);
        endpoint.port = ntohs(((Socket::Address_in&) addr).sin_port);
        manager.callbackHandler(Callback::Type::ON_MESSAGE_RECEPTION, Enum::Connection::Type::UDP, manager.getClientIdBy<Data::Endpoint>(endpoint), datagram);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::Network::Protocol::Udp::sendToEndpoint(Data::Endpoint endpoint, std::vector<std::uint8_t>& msg)
{
    try {
        Socket::Address_in servAddr = {0};

        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(endpoint.port);
        servAddr.sin_addr.s_addr = inet_addr(endpoint.address.c_str());
        _socket.sendTo(msg, msg.size(), 0, (const Socket::Address&) servAddr, sizeof(servAddr));
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
