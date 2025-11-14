
#pragma once

#include <optional>
#include <string>

namespace Dufos::Database
{
    class Users
    {
        public:
            struct User {
                std::string name;
                std::string password;
            };

            /**
             * @brief Create a new user in the database
             *
             * @param user The user to create
             * @return bool True if the user was created successfully, false otherwise
             */
            static bool create(User user);

            /**
             * @brief Get a user by name from the database
             *
             * @param name The name of the user to get
             * @return User The user with the given name
             */
            static std::optional<User> getByName(const std::string& name);
    };
};
