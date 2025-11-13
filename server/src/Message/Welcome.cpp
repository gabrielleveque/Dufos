/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Welcome
*/

#include "Message/Welcome.hpp"
#include "Message/Message.hpp"
#include "Server.hpp"
#include "Bytes.hpp"

#include <iostream>

Dufos::Message::Welcome::Welcome()
{
    _type = IMessage::Type::TO_EXECUTE;
}

bool Dufos::Message::Welcome::execute(Server& server, std::uint32_t id)
{
    Network::NetworkManager& manager = Network::NetworkManager::getInstance();
    std::vector<std::uint8_t> msg = {static_cast<std::uint8_t>(Message::Name::WELCOME), 0, 0, 0, 4};
    std::vector<std::uint8_t> idBytes;

    if (id == 0) {
        return false;
    }
    idBytes = Network::Bytes::numberToBytes(id, 4);
    msg.insert(msg.end(), idBytes.begin(), idBytes.end());
    manager.sendMessageTo(Network::Enum::Connection::Type::TCP, {id}, msg);
    return true;
}
