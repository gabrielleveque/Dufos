
#include "Env.hpp"

#include <fstream>

Dufos::Env::Variables Dufos::Env::_variables;


Dufos::Env::Variables Dufos::Env::get()
{
    return _variables;
}

void Dufos::Env::loadEnv()
{
    std::ifstream file(PATH_TO_ENV_FILE);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open .env file");
    }
    while (std::getline(file, line)) {
        if (line.starts_with("MONGODB_ROOT_USERNAME=")) {
            _variables.MONGODB_ROOT_USERNAME = loadString(line);
        } else if (line.starts_with("MONGODB_ROOT_PASSWORD=")) {
            _variables.MONGODB_ROOT_PASSWORD = loadString(line);
        } else if (line.starts_with("MONGODB_PORT=")) {
            _variables.MONGODB_PORT = static_cast<std::uint16_t>(loadNumber(line));
        }
    }
    file.close();
}

std::string Dufos::Env::loadString(std::string& line)
{
    std::string value = line.substr(line.find('=') + 1);

    if (value.starts_with("\"") && value.ends_with("\"")) {
        value = value.substr(1, value.size() - 2);
    }
    return value;
}

std::uint32_t Dufos::Env::loadNumber(std::string& line)
{
    return std::stoul(line.substr(line.find('=') + 1));
}
