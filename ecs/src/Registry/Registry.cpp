#include "Registry/Registry.hpp"

Engine::Ecs::Registry::Registry() : _nextEntityId(0) {}

Engine::Ecs::Registry::~Registry() = default;

Engine::Ecs::Entity Engine::Ecs::Registry::createEntity(const std::string& name)
{
    return Entity(name, shared_from_this(), _nextEntityId++);
}
