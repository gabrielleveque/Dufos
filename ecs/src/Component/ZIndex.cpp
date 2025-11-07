#include "Component/ZIndex.hpp"

namespace Engine::Ecs::Component
{
    ZIndex::ZIndex(std::size_t index) : _zIndex(index) {}

    std::size_t ZIndex::getIndex() const
    {
        return _zIndex;
    }

    void ZIndex::setIndex(std::size_t index)
    {
        _zIndex = index;
    }
}
