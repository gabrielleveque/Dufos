#pragma once
#include <string>

class Registry;

class Entity
{
    public:
        Entity(const std::string& entityName, Registry* reg, unsigned int entityId);

        unsigned int getId() const;
        const std::string& getName() const;
        void setName(const std::string& newName);

        template<typename T>
        void add(const T& component);

        template<typename T, typename... Args>
        void add(Args&&... args);

        template<typename T>
        T* get();

        template<typename T>
        bool has();

        template<typename T>
        void remove();

    private:
        Registry* _registry;
        unsigned int _id;
        std::string _name;
};
