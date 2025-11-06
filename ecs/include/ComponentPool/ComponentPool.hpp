#pragma once
#include <vector>
#include <unordered_map>
#include <optional>

template<typename T>
class ComponentPool
{
    public:
        void add(unsigned int entityId, const T& component);
        void remove(unsigned int entityId);
        T* get(unsigned int entityId);
        bool has(unsigned int entityId) const;
        size_t size() const;

    private:
        std::vector<T> _dense;
        std::unordered_map<unsigned int, size_t> _sparse;
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
