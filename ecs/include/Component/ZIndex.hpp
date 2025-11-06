#pragma once

class ZIndex
{
    public:
        /**
         * @brief Create a Z index.
         *
         * @param index The Z index.
         */
        ZIndex(int index = 0);

        /**
         * @brief Get the Z index.
         *
         * @return The Z index.
         */
        int getIndex() const;

        /**
         * @brief Set the Z index.
         *
         * @param index The Z index.
         */
        void setIndex(int index);

    private:
        int _zIndex;  /*!< The Z index */
};
