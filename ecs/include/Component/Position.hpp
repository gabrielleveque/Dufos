#pragma once

class Position
{
    public:
        /**
         * @brief Create a position.
         *
         * @param posX The X coordinate.
         * @param posY The Y coordinate.
         */
        Position(float posX = 0.0f, float posY = 0.0f);

        /**
         * @brief Get the X coordinate.
         *
         * @return The X coordinate.
         */
        float getX() const;

        /**
         * @brief Get the Y coordinate.
         *
         * @return The Y coordinate.
         */
        float getY() const;

        /**
         * @brief Set the X coordinate.
         *
         * @param posX The X coordinate.
         */
        void setX(float posX);

        /**
         * @brief Set the Y coordinate.
         *
         * @param posY The Y coordinate.
         */
        void setY(float posY);

        /**
         * @brief Set the position.
         *
         * @param posX The X coordinate.
         * @param posY The Y coordinate.
         */
        void setPosition(float posX, float posY);

    private:
        float _x;  /*!< The X coordinate */
        float _y;  /*!< The Y coordinate */
};
