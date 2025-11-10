#pragma once
#include <raylib.h>
#include <string>
#include <memory>
#include <cstdint>
#include "Component/Position.hpp"
#include "Component/Scale.hpp"

namespace Engine::Ecs::Component
{
    class Sprite
    {
        public:
            /**
             * @brief Create a sprite.
             */
            Sprite();

            /**
             * @brief Create a sprite with a texture.
             *
             * @param path The path to the texture file.
             */
            Sprite(const std::string& path);

            /**
             * @brief Create an animated sprite.
             *
             * @param path The path to the texture file.
             * @param frameWidth The width of each frame.
             * @param frameHeight The height of each frame.
             * @param frameCount The number of frames.
             * @param frameDuration The duration of each frame.
             * @param columns The number of columns in the sprite sheet.
             */
            Sprite(const std::string& path, std::uint16_t frameWidth, std::uint16_t frameHeight, std::uint16_t frameCount, float frameDuration, std::uint8_t columns);

            /**
             * @brief Destroy the sprite.
             */
            ~Sprite();

            /**
             * @brief Load a texture from file.
             *
             * @param path The path to the texture file.
             */
            void load(const std::string& path);

            /**
             * @brief Unload the texture.
             */
            void unload();

            /**
             * @brief Get the width of the sprite.
             *
             * @return The width of the sprite.
             */
            std::uint16_t getSpriteWidth() const;

            /**
             * @brief Get the height of the sprite.
             *
             * @return The height of the sprite.
             */
            std::uint16_t getSpriteHeight() const;

            /**
             * @brief Set the frame size for animation.
             *
             * @param width The width of each frame.
             * @param height The height of each frame.
             * @param count The number of frames.
             * @param duration The duration of each frame.
             * @param cols The number of columns in the sprite sheet.
             */
            void setFrameSize(std::uint16_t width, std::uint16_t height, std::uint16_t count, float duration, std::uint8_t cols);

            /**
             * @brief Update the animation.
             *
             * @param dt The delta time.
             */
            void updateAnimation(float dt);

            /**
             * @brief Draw the sprite.
             *
             * @param pos The position of the sprite.
             * @param scale The scale of the sprite.
             */
            void drawSprite(Position& pos, Scale& scale);

            /**
             * @brief Set the origin point of the sprite.
             *
             * @param x The X coordinate of the origin.
             * @param y The Y coordinate of the origin.
             */
            void setOrigin(float x, float y);

        private:
            std::shared_ptr<Texture2D> _texture;  /*!< The texture */
            std::string _texturePath;             /*!< The path to the texture */

            bool _animated;              /*!< Is the sprite animated */
            std::uint16_t _frameWidth;   /*!< The width of each frame */
            std::uint16_t _frameHeight;  /*!< The height of each frame */
            std::uint16_t _frameCount;   /*!< The number of frames */
            float _frameDuration;        /*!< The duration of each frame */
            std::uint8_t _columns;       /*!< The number of columns in the sprite sheet */
            std::uint16_t _currentFrame; /*!< The current frame */
            float _animTime;             /*!< The animation time */

            Vector2 _origin;         /*!< The origin point */
    };
}
