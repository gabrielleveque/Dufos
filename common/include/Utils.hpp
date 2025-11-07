#pragma once

#include <thread>

namespace Common
{
    class Utils
    {
        public:
            /**
             * @brief Joins a thread if it's joinable
             *
             * @param thread The thread to join
             */
            static void joinThread(std::thread &thread);
    };
}
