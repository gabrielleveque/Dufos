#include "Entity/Entity.hpp"

Engine::Ecs::Entity::Entity(const std::string& entityName, std::shared_ptr<Registry> reg, std::size_t entityId)
    : _registry(reg), _id(entityId), _name(entityName) {}

std::size_t Engine::Ecs::Entity::getId() const
{
    return _id;
}

const std::string& Engine::Ecs::Entity::getName() const
{
    return _name;
}

void Engine::Ecs::Entity::setName(const std::string& newName)
{
    _name = newName;
}
