#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <any>
#include "ComponentPool/ComponentPool.hpp"
#include "Entity/Entity.hpp"

class Registry
{
    public:
        Registry();
        ~Registry();

        Entity createEntity(const std::string& name);

        template<typename T>
        void addComponent(unsigned int entityId, const T& component);

        template<typename T, typename... Args>
        void addComponent(unsigned int entityId, Args&&... args);

        template<typename T>
        T* getComponent(unsigned int entityId);

        template<typename T>
        bool hasComponent(unsigned int entityId);

        template<typename T>
        void removeComponent(unsigned int entityId);

    private:
        std::unordered_map<std::type_index, std::any> _componentPools;
        unsigned int _nextEntityId;

        template<typename T>
        ComponentPool<T>& getPool();
};

template<typename T>
void Registry::addComponent(unsigned int entityId, const T& component)
{
    getPool<T>().add(entityId, component);
}

template<typename T, typename... Args>
void Registry::addComponent(unsigned int entityId, Args&&... args)
{
    getPool<T>().add(entityId, T(std::forward<Args>(args)...));
}

template<typename T>
T* Registry::getComponent(unsigned int entityId)
{
    return getPool<T>().get(entityId);
}

template<typename T>
bool Registry::hasComponent(unsigned int entityId)
{
    return getPool<T>().has(entityId);
}

template<typename T>
void Registry::removeComponent(unsigned int entityId)
{
    getPool<T>().remove(entityId);
}

template<typename T>
ComponentPool<T>& Registry::getPool()
{
    std::type_index typeIndex(typeid(T));

    auto it = _componentPools.find(typeIndex);
    if (it == _componentPools.end())
    {
        _componentPools[typeIndex] = ComponentPool<T>();
    }

    return std::any_cast<ComponentPool<T>&>(_componentPools[typeIndex]);
}

template<typename T>
void Entity::add(const T& component)
{
    _registry->addComponent<T>(_id, component);
}

template<typename T, typename... Args>
void Entity::add(Args&&... args)
{
    _registry->addComponent<T>(_id, std::forward<Args>(args)...);
}

template<typename T>
T* Entity::get()
{
    return _registry->getComponent<T>(_id);
}

template<typename T>
bool Entity::has()
{
    return _registry->hasComponent<T>(_id);
}

template<typename T>
void Entity::remove()
{
    _registry->removeComponent<T>(_id);
}
