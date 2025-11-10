#pragma once

namespace Engine::Ecs::Component
{
    class Scale
    {
        public:
            /**
             * @brief Create a scale.
             *
             * @param x The X scale.
             * @param y The Y scale.
             */
            Scale(float x = 1.0f, float y = 1.0f);

            /**
             * @brief Get the X scale.
             *
             * @return The X scale.
             */
            float getX() const;

            /**
             * @brief Get the Y scale.
             *
             * @return The Y scale.
             */
            float getY() const;

            /**
             * @brief Set the X scale.
             *
             * @param x The X scale.
             */
            void setX(float x);

            /**
             * @brief Set the Y scale.
             *
             * @param y The Y scale.
             */
            void setY(float y);

            /**
             * @brief Set the scale.
             *
             * @param x The X scale.
             * @param y The Y scale.
             */
            void setScale(float x, float y);

            /**
             * @brief Set the uniform scale.
             *
             * @param s The uniform scale.
             */
            void setUniform(float s);

        private:
            float _scaleX;  /*!< The X scale */
            float _scaleY;  /*!< The Y scale */
    };
}
