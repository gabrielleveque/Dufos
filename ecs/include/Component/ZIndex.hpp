#pragma once
#include <cstddef>

namespace Engine::Ecs::Component
{
    class ZIndex
    {
        public:
            /**
             * @brief Create a Z index.
             *
             * @param index The Z index.
             */
            ZIndex(std::size_t index = 0);

            /**
             * @brief Get the Z index.
             *
             * @return The Z index.
             */
            std::size_t getIndex() const;

            /**
             * @brief Set the Z index.
             *
             * @param index The Z index.
             */
            void setIndex(std::size_t index);

        private:
            std::size_t _zIndex;  /*!< The Z index */
    };
}
