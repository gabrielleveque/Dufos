#pragma once
#include <string>

class Registry;

class Entity
{
    public:
        /**
         * @brief Create an entity.
         *
         * @param entityName The name of the entity.
         * @param reg The registry.
         * @param entityId The ID of the entity.
         */
        Entity(const std::string& entityName, Registry* reg, unsigned int entityId);

        /**
         * @brief Get the ID of the entity.
         *
         * @return The ID of the entity.
         */
        unsigned int getId() const;

        /**
         * @brief Get the name of the entity.
         *
         * @return The name of the entity.
         */
        const std::string& getName() const;

        /**
         * @brief Set the name of the entity.
         *
         * @param newName The new name.
         */
        void setName(const std::string& newName);

        /**
         * @brief Add a component to the entity.
         *
         * @param component The component to add.
         */
        template<typename T>
        void add(const T& component);

        /**
         * @brief Add a component to the entity.
         *
         * @param args The arguments to create the component.
         */
        template<typename T, typename... Args>
        void add(Args&&... args);

        /**
         * @brief Get a component from the entity.
         *
         * @return The component.
         */
        template<typename T>
        T* get();

        /**
         * @brief Check if the entity has a component.
         *
         * @return True if the entity has the component.
         */
        template<typename T>
        bool has();

        /**
         * @brief Remove a component from the entity.
         */
        template<typename T>
        void remove();

    private:
        Registry* _registry;      /*!< The registry */
        unsigned int _id;         /*!< The ID of the entity */
        std::string _name;        /*!< The name of the entity */
};
