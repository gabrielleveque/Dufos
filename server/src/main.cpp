
#include "NetworkManager.hpp"
#include "Server.hpp"

#include <sodium.h>
#include <iostream>

int main(void)
{
    try {
        if (sodium_init() < 0) {
            throw std::runtime_error("Failed to initialize libsodium");
        }
        Dufos::Server server(LOCALHOST, 8080);

        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
        return 1;
    }
    return 0;
}
