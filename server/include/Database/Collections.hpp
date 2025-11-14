
#pragma once

#include "Singleton.hpp"

#include <mongocxx/database.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>

namespace Dufos::Database
{
    class Collections : public Common::Singleton<Collections>
    {
        public:
            /**
             * @brief Construct a new Collections object
             */
            Collections();

            /**
             * @brief Get the MongoDB client
             *
             * @param name The name of the collection
             * @return mongocxx::client& The MongoDB client
             */
            mongocxx::collection getCollection(std::string name);

        private:
            friend class Singleton<Collections>; /*!< Friend class to allow access to the private constructor and destructor */

            mongocxx::instance _instance; /*!< The MongoDB instance */
            mongocxx::client _client;     /*!< The mongodb client */
            mongocxx::database _db;       /*!< The mongodb database */
    };
};
