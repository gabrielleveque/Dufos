
#pragma once

#include "Enum/Connection.hpp"
#include "Data/Endpoint.hpp"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#endif

#include <optional>
#include <cstdint>
#include <vector>
#include <any>

namespace Engine::Network
{
#ifdef _WIN32
    /**
     * @brief Invalid file descriptor for Windows
     */
    constexpr std::int32_t INVALID_FD = INVALID_SOCKET;

    /**
     * @brief Socket error code for Windows
     */
    constexpr std::int32_t SOCKET_ERROR_CODE = SOCKET_ERROR;
#else
    /**
     * @brief Invalid file descriptor for Unix
     */
    constexpr std::int32_t INVALID_FD = -1;

    /**
     * @brief Socket error code for Unix
     */
    constexpr std::int32_t SOCKET_ERROR_CODE = -1;
#endif

    class Socket
    {
        public:
            /**
             * @brief Optional reference wrapper
             *
             * @tparam T The type of the object to wrap
             */
            template <typename T>
            using OptionalReference = std::optional<std::reference_wrapper<T>>;

            /**
             * @brief Socket address
             */
            using Address = struct sockaddr;

            /**
             * @brief Socket address, internet style

             */
            using Address_in = struct sockaddr_in;

#ifdef _WIN32
            /**
             * @brief Length type for addresses on Windows
             */
            using AddressLength = std::int32_t;

            /**
             * @brief File descriptor type for Windows
             */
            using Fd = SOCKET;

            /**
             * @brief nfds_t type for Windows
             */
            using NFDS = ULONG;

            /**
             * @brief Type for number of bytes sent on Windows
             */
            using BytesSent = std::int32_t;

            /**
             * @brief Type for number of bytes received on Windows
             */
            using BytesReceived = std::int32_t;

            /**
             * @brief Type for buffer length on Windows
             */
            using BufferLength = std::int32_t;
            /**
             * @brief in_addr type for Windows
             */
            using InAddr = u_short;
#else
            /**
             * @brief Length type for addresses on Unix
             */
            using AddressLength = socklen_t;

            /**
             * @brief File descriptor type for Unix
             */
            using Fd = std::int32_t;

            /**
             * @brief nfds_t type for Unix
             */
            using NFDS = nfds_t;

            /**
             * @brief Type for number of bytes sent on Unix
             */
            using BytesSent = ssize_t;

            /**
             * @brief Type for number of bytes received on Unix
             */
            using BytesReceived = ssize_t;

            /**
             * @brief Type for buffer length on Unix
             */
            using BufferLength = std::size_t;
            /**
             * @brief in_addr type for Unix
             */
            using InAddr = in_addr_t;
#endif

            /**
             * @brief Pollfd structure for Unix
             */
            using PollFd = struct pollfd;

            /**
             * @brief Buffer type
             */
            using Buffer = std::vector<std::uint8_t>;

            /**
             * @brief Construct a new Socket object
             *
             * @param type The type of the socket (TCP or UDP)
             */
            Socket(Enum::Connection::Type type, Data::Endpoint endpoint);

            /**
             * @brief Construct a new Socket object from an existing file descriptor
             *
             * @param fd The file descriptor of the existing socket
             */
            Socket(Fd fd, bool isOwner = false);

            /**
             * @brief Default constructor of the Socket object (deleted)
             */
            Socket() = delete;

            /**
             * @brief Destroy the Socket object
             */
            ~Socket();

            /**
             * @brief Initialize the use of sockets
             */
            static void startup();

            /**
             * @brief Cleanup the use of sockets
             */
            static void cleanup();

            /**
             * @brief Bind the socket to an address
             *
             * @param addr The address to bind to
             * @param addrLen The length of the address
             */
            void bind(const Address& addr, AddressLength addrLen);

            /**
             * @brief Listen for incoming connections
             *
             * @param backlog The maximum length of the queue of pending connections
             */
            void listen(std::int32_t backlog = SOMAXCONN);

            /**
             * @brief Enable the reuse of the address and port
             *
             * @param enable Whether to enable or disable the option
             */
            void reuse(bool enable = true);

            /**
             * @brief Accept a new connection
             *
             * @param addr (Optional) Pointer to an Address structure to store the address of the connecting entity
             * @param addrLen (Optional) Pointer to an AddressLength variable to store the length of the address
             * @return Fd The file descriptor for the accepted socket
             */
            Socket accept(OptionalReference<Address> addr = std::nullopt, OptionalReference<AddressLength> addrLen = std::nullopt);

            /**
             * @brief Connect to a remote address
             *
             * @param addr The address to connect to
             * @param addrLen The length of the address
             * @return std::int8_t 0 on success, -1 on failure
             */
            void connect(const Address& addr, AddressLength addrLen);

            /**
             * @brief Polls the socket for events
             *
             * @param fds An array of PollFd structures
             * @param nfds The number of file descriptors in the fds array
             * @param timeout The timeout in milliseconds (-1 for infinite)
             * @return std::int32_t The number of file descriptors with events, 0 on timeout, or -1 on error
             */
            std::int32_t poll(std::vector<PollFd>& fds, NFDS nfds, std::int32_t timeout);

            /**
             * @brief Sends data over the socket (for TCP sockets)
             *
             * @param buffer The data to send
             * @param length The length of the data to send
             * @param flags Flags for sending the data
             * @return BytesSent The number of bytes sent, or -1 on error
             */
            BytesSent send(const Buffer& buffer, BufferLength length, std::int32_t flags);

            /**
             * @brief Receives data from the socket (for TCP sockets)
             *
             * @param buffer The buffer to store the received data
             * @param length The maximum length of data to receive
             * @param flags Flags for receiving the data
             * @return BytesReceived The number of bytes received, or -1 on error
             */
            BytesReceived recv(Buffer& buffer, BufferLength length, std::int32_t flags);

            /**
             * @brief Sends data to a specific address (for UDP sockets)
             *
             * @param buffer The data to send
             * @param length The length of the data to send
             * @param flags Flags for sending the data
             * @param destAddr The destination address
             * @param destLen The length of the destination address
             * @return Engine::Network::Socket::BytesReceived The number of bytes sent, or -1 on error
             */
            BytesReceived sendTo(const Buffer& buffer, BufferLength length, std::int32_t flags, const Address& destAddr, AddressLength destAddrLen);

            /**
             * @brief Receives data from a specific address (for UDP sockets)
             *
             * @param buffer The buffer to store the received data
             * @param length The maximum length of data to receive
             * @param flags Flags for receiving the data
             * @param srcAddr (Optional) Pointer to an Address structure to store the source address
             * @param srcAddrLen (Optional) Pointer to an AddressLength variable to store the length of the source address
             * @return Engine::Network::Socket::BytesReceived The number of bytes received, or -1 on error
             */
            BytesReceived recvFrom(
                Buffer& buffer, BufferLength length, std::int32_t flags, OptionalReference<Address> srcAddr = std::nullopt, OptionalReference<AddressLength> srcAddrLen = std::nullopt);

            /**
             * @brief Get the socket name (local address)
             *
             * @param addr Reference to an Address structure to store the local address
             * @param addrLen Reference to an AddressLength variable to store the length of the local address
             * @return std::int32_t 0 on success, -1 on failure
             */
            std::int32_t getSockName(Address& addr, AddressLength& addrLen);

            /**
             * @brief Get the Fd object
             *
             * @return Engine::Network::Socket::Fd
             */
            Fd getFd() const;

            /**
             * @brief Get the Endpoint object
             *
             * @return Endpoint The endpoint of the socket
             */
            Data::Endpoint getEndpoint() const;

            /**
             * @brief Set the Endpoint object
             *
             * @param endpoint The new endpoint to set
             */
            void setEndpoint(Data::Endpoint endpoint);

            /**
             * @brief Convert an IP address string to an in_addr_t
             *
             * @param ip The IP address string (e.g., "192.168.1.1")
             * @return in_addr_t The converted IP address in network byte order
             */
            static InAddr inetAddr(std::string ip);

        private:
            /**
             * @brief Get the Last Error object
             *
             * @return std::string The last error message
             */
            static std::string getLastError();

            Fd _fd;                   /*!> The file descriptor of the socket */
            Data::Endpoint _endpoint; /*!> The endpoint of the socket */

            bool _isOwner; /*!> Whether the socket owns the file descriptor (for cleanup purposes) */
    };
}
