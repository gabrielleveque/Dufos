#include "Registry/Registry.hpp"

namespace Engine::Ecs
{
    Registry::Registry() : _nextEntityId(0) {}

    Registry::~Registry() {}

    Entity Registry::createEntity(const std::string& name)
    {
        Entity entity(name, shared_from_this(), _nextEntityId++);
        return entity;
    }
}
