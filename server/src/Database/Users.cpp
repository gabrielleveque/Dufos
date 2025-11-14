
#include "Database/Collections.hpp"
#include "Database/Users.hpp"

#include <bsoncxx/json.hpp>

bool Dufos::Database::Users::create(User user)
{
    try {
        Dufos::Database::Collections& collections = Dufos::Database::Collections::getInstance();
        mongocxx::collection usersCollection = collections.getCollection("users");
        bsoncxx::builder::basic::document doc;

        usersCollection.create_index(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("name", 1)), mongocxx::options::index{}.unique(true));
        doc.append(bsoncxx::builder::basic::kvp("name", user.name));
        doc.append(bsoncxx::builder::basic::kvp("password", user.password));

        auto result = usersCollection.insert_one(doc.view());
        return result.has_value();
    } catch (const std::exception& e) {
        return false;
    }
}

std::optional<Dufos::Database::Users::User> Dufos::Database::Users::getByName(const std::string& name)
{
    try {
        Dufos::Database::Collections& collections = Dufos::Database::Collections::getInstance();
        mongocxx::collection usersCollection = collections.getCollection("users");

        auto result = usersCollection.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("name", name)));
        if (!result.has_value()) {
            return std::nullopt;
        }
        bsoncxx::document::view doc = result->view();
        Users::User user;

        user.name = std::string(doc["name"].get_string().value);
        user.password = std::string(doc["password"].get_string().value);
        return user;
    } catch (const std::exception& e) {
        return std::nullopt;
    }
}
