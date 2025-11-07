#include "Component/Scale.hpp"

namespace Engine::Ecs::Component
{
    Scale::Scale(float x, float y) : _scaleX(x), _scaleY(y) {}

    float Scale::getX() const
    {
        return _scaleX;
    }

    float Scale::getY() const
    {
        return _scaleY;
    }

    void Scale::setX(float x)
    {
        _scaleX = x;
    }

    void Scale::setY(float y)
    {
        _scaleY = y;
    }

    void Scale::setScale(float x, float y)
    {
        _scaleX = x;
        _scaleY = y;
    }

    void Scale::setUniform(float s)
    {
        _scaleX = s;
        _scaleY = s;
    }
}
