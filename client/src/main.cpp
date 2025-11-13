
#include "NetworkManager.hpp"
#include "Client.hpp"

#include <iostream>

int main(void)
{
    try {
        Dufos::Client client(LOCALHOST, 8080);

        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
        return 1;
    }
    return 0;
}
