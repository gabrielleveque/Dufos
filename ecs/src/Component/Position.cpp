#include "Component/Position.hpp"

namespace Engine::Ecs::Component
{
    Position::Position(std::uint16_t posX, std::uint16_t posY) : _x(posX), _y(posY) {}

    std::uint16_t Position::getX() const
    {
        return _x;
    }

    std::uint16_t Position::getY() const
    {
        return _y;
    }

    void Position::setX(std::uint16_t posX)
    {
        _x = posX;
    }

    void Position::setY(std::uint16_t posY)
    {
        _y = posY;
    }

    void Position::setPosition(std::uint16_t posX, std::uint16_t posY)
    {
        _x = posX;
        _y = posY;
    }
}
