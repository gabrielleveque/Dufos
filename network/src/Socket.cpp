
#include "Socket.hpp"

#ifdef _WIN32

#else
#include <errno.h>
#endif

#include <cstring>
#include <format>

Network::Socket::Socket(Enum::Connection::Type type, Data::Endpoint endpoint) : _endpoint(endpoint), _isOwner(true)
{
    if (type == Enum::Connection::Type::TCP) {
        _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    } else if (type == Enum::Connection::Type::UDP) {
        _fd = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    if (_fd == INVALID_FD) {
        throw std::runtime_error(std::format("Couldn't create the socket: {}.", getLastError()));
    }
}

Network::Socket::Socket(Fd fd, bool isOwner) : _fd(fd), _isOwner(isOwner)
{
    if (fd == INVALID_FD) {
        throw std::runtime_error(std::format("Invalid file descriptor provided."));
    }
    startup();
}

Network::Socket::~Socket()
{
    if (!_isOwner) {
        return;
    }
    if (_fd != INVALID_FD) {
#ifdef _WIN32
        closesocket(_fd);
#else
        ::close(_fd);
#endif
    }
}

void Network::Socket::startup()
{
#ifdef _WIN32
    WSADATA wsaData = {0};

    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error(std::format("WSAStartup failed: {}.", getLastError()));
    }
#endif
}

void Network::Socket::cleanup()
{
#ifdef _WIN32
    ::WSACleanup();
#endif
}

void Network::Socket::bind(const Address& addr, AddressLength addrLen)
{
    if (::bind(_fd, &addr, addrLen) == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Couldn't bind the socket: {}.", getLastError()));
    }
}

void Network::Socket::listen(std::int32_t backlog)
{
    if (::listen(_fd, backlog) == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Couldn't listen on the socket: {}.", getLastError()));
    }
}

void Network::Socket::reuse(bool enable)
{
    std::uint32_t opt = 1;

#ifdef _WIN32
    if (!enable) {
        if (::setsockopt(_fd, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *) &opt, sizeof(opt)) == SOCKET_ERROR_CODE) {
            throw std::runtime_error(std::format("Couldn't set the exclusive address use option on the socket: {}.", getLastError()));
        }
    } else {
        if (::setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) == SOCKET_ERROR_CODE) {
            throw std::runtime_error(std::format("Couldn't set the reuse address option on the socket: {}.", getLastError()));
        }
    }
#else
    if (!enable) {
        return;
    }
    if (::setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == SOCKET_ERROR_CODE || ::setsockopt(_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Couldn't set the reuse options on the socket: {}.", getLastError()));
    }
#endif
}

Network::Socket Network::Socket::accept(OptionalReference<Address> addr, OptionalReference<AddressLength> addrLen)
{
    Address *addrPtr = addr.has_value() ? &addr.value().get() : nullptr;
    AddressLength *addrLenPtr = addrLen.has_value() ? &addrLen.value().get() : nullptr;
    Fd clientFd = 0;

    clientFd = ::accept(_fd, addrPtr, addrLenPtr);
    if (clientFd == INVALID_FD) {
        throw std::runtime_error(std::format("Couldn't accept the connection: {}.", getLastError()));
    }
    return clientFd;
}

void Network::Socket::connect(const Address& addr, AddressLength addrLen)
{
    if (::connect(_fd, &addr, addrLen) == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Couldn't connect to the address: {}.", getLastError()));
    }
}

std::int32_t Network::Socket::poll(std::vector<PollFd>& fds, NFDS nfds, std::int32_t timeout)
{
    std::int32_t polled = 0;

#ifdef _WIN32
    polled = ::WSAPoll(fds.data(), nfds, timeout);
#else
    polled = ::poll(fds.data(), nfds, timeout);
#endif
    if (polled == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Poll error on the socket: {}.", getLastError()));
    }
    return polled;
}

Network::Socket::BytesSent Network::Socket::send(const Buffer& buffer, BufferLength length, std::int32_t flags)
{
    BytesSent bytesSent = 0;

    bytesSent = ::send(_fd, (const char *) buffer.data(), length, flags);
    if (bytesSent == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Send error on the socket: {}.", getLastError()));
    }
    return bytesSent;
}

Network::Socket::BytesReceived Network::Socket::recv(Buffer& buffer, BufferLength length, std::int32_t flags)
{
    BytesReceived bytesReceived = 0;

    bytesReceived = ::recv(_fd, (char *) buffer.data(), length, flags);
    if (bytesReceived == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Receive error on the socket: {}.", getLastError()));
    }
    return bytesReceived;
}

Network::Socket::BytesReceived Network::Socket::sendTo(const Buffer& buffer, BufferLength length, std::int32_t flags, const Address& destAddr, AddressLength destAddrLen)
{
    BytesSent bytesSent = 0;

    bytesSent = ::sendto(_fd, (const char *) buffer.data(), length, flags, &destAddr, destAddrLen);
    if (bytesSent == SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Send error to an endpoint: {}.", getLastError()));
    }
    return bytesSent;
}

Network::Socket::BytesReceived Network::Socket::recvFrom(Buffer& buffer, BufferLength length, std::int32_t flags, OptionalReference<Address> srcAddr, OptionalReference<AddressLength> srcAddrLen)
{
    Address *addrPtr = srcAddr.has_value() ? &srcAddr->get() : nullptr;
    AddressLength *addrLenPtr = srcAddrLen.has_value() ? &srcAddrLen->get() : nullptr;
    BytesReceived bytesReceived = 0;

    bytesReceived = ::recvfrom(_fd, (char *) buffer.data(), length, flags, addrPtr, addrLenPtr);
    if (bytesReceived == SOCKET_ERROR_CODE) {

        throw std::runtime_error(std::format("Receive error from an endpoint: {}.", getLastError()));
    }
    return bytesReceived;
}

std::int32_t Network::Socket::getSockName(Address& addr, AddressLength& addrLen)
{
    if (::getsockname(_fd, &addr, &addrLen) < SOCKET_ERROR_CODE) {
        throw std::runtime_error(std::format("Error getting socket name: {}.", getLastError()));
    }
    return 0;
}

Network::Socket::Fd Network::Socket::getFd() const
{
    return _fd;
}

Network::Data::Endpoint Network::Socket::getEndpoint() const
{
    return _endpoint;
}

void Network::Socket::setEndpoint(Data::Endpoint endpoint)
{
    _endpoint = endpoint;
}

std::string Network::Socket::getLastError()
{
    std::string error;

#ifdef _WIN32
    error = std::to_string(::WSAGetLastError());
#else
    error = std::string(std::strerror(errno));
#endif
    return error;
}

Network::Socket::InAddr Network::Socket::inetAddr(std::string ip)
{
    return ::inet_addr(ip.c_str());
}
