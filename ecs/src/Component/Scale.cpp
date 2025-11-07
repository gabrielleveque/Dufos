#include "Component/Scale.hpp"

Engine::Ecs::Component::Scale::Scale(float x, float y) : _scaleX(x), _scaleY(y) {}

float Engine::Ecs::Component::Scale::getX() const
{
    return _scaleX;
}

float Engine::Ecs::Component::Scale::getY() const
{
    return _scaleY;
}

void Engine::Ecs::Component::Scale::setX(float x)
{
    _scaleX = x;
}

void Engine::Ecs::Component::Scale::setY(float y)
{
    _scaleY = y;
}

void Engine::Ecs::Component::Scale::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

void Engine::Ecs::Component::Scale::setUniform(float s)
{
    _scaleX = s;
    _scaleY = s;
}
