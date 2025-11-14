
#include "Database/Collections.hpp"
#include "Env.hpp"

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <format>

Dufos::Database::Collections::Collections()
{
    Dufos::Env::Variables env = Dufos::Env::get();
    mongocxx::uri uri(std::format("mongodb://{}:{}@localhost:{}", env.MONGODB_ROOT_USERNAME, env.MONGODB_ROOT_PASSWORD, env.MONGODB_PORT));

    _client = mongocxx::client(uri);

    std::vector<std::string> names = _client.list_database_names();

    if (std::find(names.begin(), names.end(), "dufos_database") == names.end()) {
        _client["dufos_database"].create_collection("users");
    }
    _db = _client["dufos_database"];
}

mongocxx::collection Dufos::Database::Collections::getCollection(std::string name)
{
    std::vector<std::string> names = _db.list_collection_names();

    if (std::find(names.begin(), names.end(), name) == names.end()) {
        _client["dufos_database"].create_collection(name);
    }
    return _db[name];
}
