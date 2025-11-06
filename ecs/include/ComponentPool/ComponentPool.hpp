#pragma once
#include <vector>
#include <unordered_map>
#include <optional>

template<typename T>
class ComponentPool
{
    public:
        /**
         * @brief Add a component to the pool.
         *
         * @param entityId The ID of the entity.
         * @param component The component to add.
         */
        void add(unsigned int entityId, const T& component);

        /**
         * @brief Remove a component from the pool.
         *
         * @param entityId The ID of the entity.
         */
        void remove(unsigned int entityId);

        /**
         * @brief Get a component from the pool.
         *
         * @param entityId The ID of the entity.
         * @return The component.
         */
        T* get(unsigned int entityId);

        /**
         * @brief Check if the pool has a component.
         *
         * @param entityId The ID of the entity.
         * @return True if the pool has the component.
         */
        bool has(unsigned int entityId) const;

        /**
         * @brief Get the size of the pool.
         *
         * @return The size of the pool.
         */
        size_t size() const;

    private:
        std::vector<T> _dense;                              /*!< The dense array */
        std::unordered_map<unsigned int, size_t> _sparse;   /*!< The sparse map */
};

template<typename T>
void ComponentPool<T>::add(unsigned int entityId, const T& component)
{
    if (_sparse.find(entityId) != _sparse.end())
    {
        _dense[_sparse[entityId]] = component;
        return;
    }

    _sparse[entityId] = _dense.size();
    _dense.push_back(component);
}

template<typename T>
void ComponentPool<T>::remove(unsigned int entityId)
{
    auto it = _sparse.find(entityId);
    if (it == _sparse.end())
    {
        return;
    }

    size_t indexToRemove = it->second;
    size_t lastIndex = _dense.size() - 1;

    if (indexToRemove != lastIndex)
    {
        _dense[indexToRemove] = _dense[lastIndex];

        for (auto& pair : _sparse)
        {
            if (pair.second == lastIndex)
            {
                pair.second = indexToRemove;
                break;
            }
        }
    }

    _dense.pop_back();
    _sparse.erase(it);
}

template<typename T>
T* ComponentPool<T>::get(unsigned int entityId)
{
    auto it = _sparse.find(entityId);
    if (it == _sparse.end())
    {
        return nullptr;
    }

    return &_dense[it->second];
}

template<typename T>
bool ComponentPool<T>::has(unsigned int entityId) const
{
    return _sparse.find(entityId) != _sparse.end();
}

template<typename T>
size_t ComponentPool<T>::size() const
{
    return _dense.size();
}
