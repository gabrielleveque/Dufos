#pragma once

class Position
{
    public:
        Position(float posX = 0.0f, float posY = 0.0f);

        float getX() const;
        float getY() const;
        void setX(float posX);
        void setY(float posY);
        void setPosition(float posX, float posY);

    private:
        float _x;
        float _y;
};
