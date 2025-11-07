#pragma once
#include <string>
#include <memory>
#include <optional>
#include <functional>

namespace Engine::Ecs
{
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
            Entity(const std::string& entityName, std::shared_ptr<Registry> reg, std::size_t entityId);

            /**
             * @brief Get the ID of the entity.
             *
             * @return The ID of the entity.
             */
            std::size_t getId() const;

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
            std::optional<std::reference_wrapper<T>> get();

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
            std::shared_ptr<Registry> _registry;  /*!< The registry */
            std::size_t _id;                      /*!< The ID of the entity */
            std::string _name;                    /*!< The name of the entity */
    };
}
