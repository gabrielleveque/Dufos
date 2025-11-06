#include "Registry/Registry.hpp"

Registry::Registry() : _nextEntityId(0)
{
}

Registry::~Registry()
{
}

Entity Registry::createEntity(const std::string& name)
{
    Entity entity(name, this, _nextEntityId++);
    return entity;
}
