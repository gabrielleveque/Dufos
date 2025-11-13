
#pragma once

#include <string>

namespace Dufos
{
    class Password
    {
        public:
            /**
             * @brief Hash the password
             *
             * @param password The password to hash
             * @return std::string The hashed password
             */
            static std::string hashPassword(const std::string& password);

            /**
             * @brief Verify a password against a hashed password
             *
             * @param hashed The hashed password
             * @param password The password to verify
             * @return bool True if the password matches the hash, false otherwise
             */
            static bool verifyPassword(const std::string& hashed, const std::string& password);
    };
}
