
#pragma once

#include <string>

namespace Dufos
{
    class Account
    {
        public:
            /**
             * @enum Action
             * @brief The different actions for account management
             */
            enum class Action {
                REGISTER,
                LOGIN,
            };

            /**
             * @brief Account information structure
             */
            struct Info {
                    Action action;        /*!< The action to perform */
                    std::string name;     /*!< The name of the account */
                    std::string password; /*!< The password of the account */
            };

            /**
             * @brief Connect to account management system
             */
            static std::optional<Info> connectTo();

        private:
            /**
             * @brief Get the Account Name object
             *
             * @param info The account information structure to fill
             * @return bool True if successful, false otherwise
             */
            static bool getName(Info& info);

            /**
             * @brief Get the Account Password object
             *
             * @param info The account information structure to fill
             * @return bool True if successful, false otherwise
             */
            static bool getPassword(Info& info);
    };
}
