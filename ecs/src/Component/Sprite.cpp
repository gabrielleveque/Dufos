#include "Component/Sprite.hpp"
#include "Component/Position.hpp"
#include "Component/Scale.hpp"

Engine::Ecs::Component::Sprite::Sprite()
    : _texture(nullptr), _texturePath(""), _animated(false),
    _frameWidth(0), _frameHeight(0), _frameCount(1), _frameDuration(0.1f),
    _columns(1), _currentFrame(0), _animTime(0.0f),
    _origin{0, 0} {}

Engine::Ecs::Component::Sprite::Sprite(const std::string& path)
    : _texturePath(path), _animated(false),
    _frameWidth(0), _frameHeight(0), _frameCount(1), _frameDuration(0.1f),
    _columns(1), _currentFrame(0), _animTime(0.0f),
    _origin{0, 0}
{
    load(path);
}

Engine::Ecs::Component::Sprite::Sprite(const std::string& path, std::uint16_t frameWidth, std::uint16_t frameHeight, std::uint16_t frameCount, float frameDuration, std::uint8_t columns)
    : _texturePath(path), _animated(true), _frameWidth(frameWidth),
    _frameHeight(frameHeight), _frameCount(frameCount), _frameDuration(frameDuration),
    _columns(columns), _currentFrame(0), _animTime(0.0f),
    _origin{0, 0}
{
    load(path);
}

Engine::Ecs::Component::Sprite::~Sprite()
{
    unload();
}

void Engine::Ecs::Component::Sprite::load(const std::string& path)
{
    _texturePath = path;
    Texture2D* tex = new Texture2D();
    *tex = LoadTexture(path.c_str());
    _texture = std::shared_ptr<Texture2D>(tex, [](Texture2D* t) {
        if (t->id != 0) {
            UnloadTexture(*t);
        }
        delete t;
    });
}

void Engine::Ecs::Component::Sprite::unload()
{
    _texture.reset();
}

std::uint16_t Engine::Ecs::Component::Sprite::getSpriteWidth() const
{
    if (_animated) {
        return _frameWidth;
    }
    return _texture ? _texture->width : 0;
}

std::uint16_t Engine::Ecs::Component::Sprite::getSpriteHeight() const
{
    if (_animated) {
        return _frameHeight;
    }
    return _texture ? _texture->height : 0;
}

void Engine::Ecs::Component::Sprite::setFrameSize(std::uint16_t width, std::uint16_t height, std::uint16_t count, float duration, std::uint8_t cols)
{
    _animated = true;
    _frameWidth = width;
    _frameHeight = height;
    _frameCount = count;
    _frameDuration = duration;
    _columns = cols;
    _currentFrame = 0;
    _animTime = 0.0f;
}

void Engine::Ecs::Component::Sprite::updateAnimation(float dt)
{
    if (!_animated) {
        return;
    }

    _animTime += dt;

    if (_frameDuration > 0.0f) {
        while (_animTime >= _frameDuration) {
            _animTime -= _frameDuration;
            _currentFrame = (_currentFrame + 1) % _frameCount;
        }
    }
}

void Engine::Ecs::Component::Sprite::drawSprite(Position& pos, Scale& scale)
{
    if (!_texture || _texture->id == 0) {
        return;
    }

    Vector2 position = {static_cast<float>(pos.getX()), static_cast<float>(pos.getY())};

    if (!_animated) {
        float avgScale = (scale.getX() + scale.getY()) / 2.0f;
        DrawTextureEx(*_texture.get(), position, 0.0f, avgScale, WHITE);
        return;
    }

    Rectangle frameRec = {
        static_cast<float>((_currentFrame % _columns) * _frameWidth),
        static_cast<float>((_currentFrame / _columns) * _frameHeight),
        static_cast<float>(_frameWidth),
        static_cast<float>(_frameHeight)
    };

    Rectangle destRec = {
        position.x,
        position.y,
        static_cast<float>(_frameWidth) * scale.getX(),
        static_cast<float>(_frameHeight) * scale.getY()
    };

    DrawTexturePro(*_texture.get(), frameRec, destRec, _origin, 0.0f, WHITE);
}

void Engine::Ecs::Component::Sprite::setOrigin(float x, float y)
{
    _origin.x = x;
    _origin.y = y;
}
