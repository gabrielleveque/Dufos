#pragma once
#include <raylib.h>
#include <string>
#include <memory>

class Position;
class Scale;

class Sprite
{
    public:
        Sprite();
        Sprite(const std::string& path);
        Sprite(const std::string& path, int frameWidth, int frameHeight, int frameCount, float frameDuration, int columns);
        ~Sprite();

        void load(const std::string& path);
        void unload();

        int getSpriteWidth() const;
        int getSpriteHeight() const;

        void setFrameSize(int width, int height, int count, float duration, int cols);
        void updateAnimation(float dt);
        void drawSprite(Position& pos, Scale& scale);

        void setOrigin(float x, float y);

    private:
        std::shared_ptr<Texture2D> _texture;
        std::string _texturePath;

        bool _animated;
        int _frameWidth;
        int _frameHeight;
        int _frameCount;
        float _frameDuration;
        int _columns;
        int _currentFrame;
        float _animTime;

        Vector2 _origin;
};
