#include "Entity/Entity.hpp"

Entity::Entity(const std::string& entityName, Registry* reg, unsigned int entityId)
    : _registry(reg), _id(entityId), _name(entityName)
{
}

unsigned int Entity::getId() const
{
    return _id;
}

const std::string& Entity::getName() const
{
    return _name;
}

void Entity::setName(const std::string& newName)
{
    _name = newName;
}
