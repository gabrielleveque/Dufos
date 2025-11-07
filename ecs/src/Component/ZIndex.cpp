#include "Component/ZIndex.hpp"

Engine::Ecs::Component::ZIndex::ZIndex(std::size_t index) : _zIndex(index) {}

std::size_t Engine::Ecs::Component::ZIndex::getIndex() const
{
    return _zIndex;
}

void Engine::Ecs::Component::ZIndex::setIndex(std::size_t index)
{
    _zIndex = index;
}
