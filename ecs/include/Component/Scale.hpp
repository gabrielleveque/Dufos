#pragma once

class Scale
{
    public:
        Scale(float x = 1.0f, float y = 1.0f);

        float getX() const;
        float getY() const;
        void setX(float x);
        void setY(float y);
        void setScale(float x, float y);
        void setUniform(float s);

    private:
        float _scaleX;
        float _scaleY;
};
