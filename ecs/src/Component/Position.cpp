#include "Component/Position.hpp"

Position::Position(float posX, float posY) : _x(posX), _y(posY)
{
}

float Position::getX() const
{
    return _x;
}

float Position::getY() const
{
    return _y;
}

void Position::setX(float posX)
{
    _x = posX;
}

void Position::setY(float posY)
{
    _y = posY;
}

void Position::setPosition(float posX, float posY)
{
    _x = posX;
    _y = posY;
}
