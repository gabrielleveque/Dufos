#pragma once
#include <cstdint>

namespace Engine::Ecs::Component
{
    class Position
    {
        public:
            /**
             * @brief Create a position.
             *
             * @param posX The X coordinate.
             * @param posY The Y coordinate.
             */
            Position(std::uint16_t posX = 0, std::uint16_t posY = 0);

            /**
             * @brief Get the X coordinate.
             *
             * @return The X coordinate.
             */
            std::uint16_t getX() const;

            /**
             * @brief Get the Y coordinate.
             *
             * @return The Y coordinate.
             */
            std::uint16_t getY() const;

            /**
             * @brief Set the X coordinate.
             *
             * @param posX The X coordinate.
             */
            void setX(std::uint16_t posX);

            /**
             * @brief Set the Y coordinate.
             *
             * @param posY The Y coordinate.
             */
            void setY(std::uint16_t posY);

            /**
             * @brief Set the position.
             *
             * @param posX The X coordinate.
             * @param posY The Y coordinate.
             */
            void setPosition(std::uint16_t posX, std::uint16_t posY);

        private:
            std::uint16_t _x;  /*!< The X coordinate */
            std::uint16_t _y;  /*!< The Y coordinate */
    };
}
