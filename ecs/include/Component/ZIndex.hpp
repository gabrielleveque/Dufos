#pragma once

class ZIndex
{
    public:
        ZIndex(int index = 0);

        int getIndex() const;
        void setIndex(int index);

    private:
        int _zIndex;
};
