#include "Entity/Entity.hpp"

namespace Engine::Ecs
{
    Entity::Entity(const std::string& entityName, std::shared_ptr<Registry> reg, std::size_t entityId)
        : _registry(reg), _id(entityId), _name(entityName) {}

    std::size_t Entity::getId() const
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
}
