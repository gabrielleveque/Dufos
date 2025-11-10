#include "Component/Position.hpp"

Engine::Ecs::Component::Position::Position(std::uint16_t posX, std::uint16_t posY) : _x(posX), _y(posY) {}

std::uint16_t Engine::Ecs::Component::Position::getX() const
{
    return _x;
}

std::uint16_t Engine::Ecs::Component::Position::getY() const
{
    return _y;
}

void Engine::Ecs::Component::Position::setX(std::uint16_t posX)
{
    _x = posX;
}

void Engine::Ecs::Component::Position::setY(std::uint16_t posY)
{
    _y = posY;
}

void Engine::Ecs::Component::Position::setPosition(std::uint16_t posX, std::uint16_t posY)
{
    _x = posX;
    _y = posY;
}
