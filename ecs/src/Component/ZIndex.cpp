#include "Component/ZIndex.hpp"

ZIndex::ZIndex(int index) : _zIndex(index)
{
}

int ZIndex::getIndex() const
{
    return _zIndex;
}

void ZIndex::setIndex(int index)
{
    _zIndex = index;
}
