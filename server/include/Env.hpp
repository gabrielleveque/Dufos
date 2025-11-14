
#pragma once

#include <unordered_map>
#include <string>
#include <any>

#define PATH_TO_ENV_FILE ".env"

namespace Dufos
{
    class Env
    {
        public:
            /**
             * @struct EnvVariable
             * @brief Structure to hold environment variable keys
             */
            struct Variables {
                    std::string MONGODB_ROOT_USERNAME; /*!< MongoDB root username */
                    std::string MONGODB_ROOT_PASSWORD; /*!< MongoDB root password */
                    std::uint16_t MONGODB_PORT;        /*!< MongoDB port */
            };

            // /**
            //  * @brief Construct a new Env object
            //  *
            //  * @param load if the env should be loaded or not
            //  */
            // Env(bool load = false);

            /**
             * @brief Get the value of an environment variable
             *
             * @return Variables The value of the environment variable
             */
            static Variables get();

            /**
             * @brief Load the environment variables from the .env file
             */
            static void loadEnv();

        private:
            /**
             * @brief Load a string from a line
             *
             * @param line The line to load the string from
             * @return std::string The loaded string
             */
            static std::string loadString(std::string& line);

            /**
             * @brief Load a number from a line
             *
             * @param line The line to load the number from
             * @return std::uint32_t The loaded number
             */
            static std::uint32_t loadNumber(std::string& line);

            static Variables _variables; /*!< The environment variables */
    };
}
