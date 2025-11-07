
#pragma once

namespace Common
{
    template <typename T>
    class Singleton
    {
        public:
            /**
             * @brief Delete the copy constructor of the Singleton class
             */
            Singleton(Singleton const &) = delete;

            /**
             * @brief Delete the assignement operator of the Singleton class
             */
            Singleton& operator=(Singleton const &) = delete;

            /**
             * @brief Get the Instance object
             *
             * @return T& The retrieved instance
             */
            static T& getInstance()
            {
                static T instance;
                return instance;
            }

        protected:
            /**
             * @brief Default constructor of the Singleton class
             */
            Singleton() = default;

            /**
             * @brief Default destructor of the Singleton class
             */
            ~Singleton() = default;
    };
}
