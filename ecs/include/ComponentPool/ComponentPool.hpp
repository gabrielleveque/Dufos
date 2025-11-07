#pragma once
#include <vector>
#include <unordered_map>
#include <optional>

namespace Engine::Ecs
{
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
            void add(std::size_t entityId, const T& component);

            /**
             * @brief Remove a component from the pool.
             *
             * @param entityId The ID of the entity.
             */
            void remove(std::size_t entityId);

            /**
             * @brief Get a component from the pool.
             *
             * @param entityId The ID of the entity.
             * @return The component.
             */
            std::optional<std::reference_wrapper<T>> get(std::size_t entityId);

            /**
             * @brief Check if the pool has a component.
             *
             * @param entityId The ID of the entity.
             * @return True if the pool has the component.
             */
            bool has(std::size_t entityId) const;

            /**
             * @brief Get the size of the pool.
             *
             * @return The size of the pool.
             */
            size_t size() const;

        private:
            std::vector<T> _dense;                                 /*!< The dense array */
            std::unordered_map<std::size_t, std::size_t> _sparse;  /*!< The sparse map */
    };

    template<typename T>
    void ComponentPool<T>::add(std::size_t entityId, const T& component)
    {
        if (_sparse.find(entityId) != _sparse.end()) {
            _dense[_sparse[entityId]] = component;
            return;
        }

        _sparse[entityId] = _dense.size();
        _dense.push_back(component);
    }

    template<typename T>
    void ComponentPool<T>::remove(std::size_t entityId)
    {
        auto it = _sparse.find(entityId);
        if (it == _sparse.end()) {
            return;
        }

        std::size_t indexToRemove = it->second;
        std::size_t lastIndex = _dense.size() - 1;

        if (indexToRemove != lastIndex) {
            _dense[indexToRemove] = _dense[lastIndex];

            for (auto& pair : _sparse) {
                if (pair.second == lastIndex) {
                    pair.second = indexToRemove;
                    break;
                }
            }
        }

        _dense.pop_back();
        _sparse.erase(it);
    }

    template<typename T>
    std::optional<std::reference_wrapper<T>> ComponentPool<T>::get(std::size_t entityId)
    {
        auto it = _sparse.find(entityId);
        if (it == _sparse.end()) {
            return std::nullopt;
        }

        return std::ref(_dense[it->second]);
    }

    template<typename T>
    bool ComponentPool<T>::has(std::size_t entityId) const
    {
        return _sparse.find(entityId) != _sparse.end();
    }

    template<typename T>
    std::size_t ComponentPool<T>::size() const
    {
        return _dense.size();
    }
}
