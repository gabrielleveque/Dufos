/*
** EPITECH PROJECT, 2025
** dufos
** File description:
** Message
*/

#include "Message/Welcome.hpp"
#include "Message/Message.hpp"

#include <format>

std::unordered_map<Dufos::Message::Message::Name, std::shared_ptr<Dufos::Message::IMessage>> Dufos::Message::Message::_messages = {
    {Dufos::Message::Message::Name::WELCOME, std::make_shared<Dufos::Message::Welcome>()},
};

bool Dufos::Message::Message::sendMessage(Name name, Client& client, std::uint32_t id)
{
    try {
        bool success = false;

        if (_messages.find(name) == _messages.end() || !_messages[name] || !_messages[name]->getType().contains(IMessage::Type::TO_EXECUTE)) {
            return false;
        }
        success = _messages[name]->execute(client, id);
        return success;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Dufos::Message::Message::recvMessage(Network::Data::Message& message, Client& client, std::uint32_t id)
{
    try {
        Name name = static_cast<Name>(message.opcode);
        bool success = false;

        if (_messages.find(name) == _messages.end() || !_messages[name] || !_messages[name]->getType().contains(IMessage::Type::TO_PROCESS)) {
            return false;
        }
        success = _messages[name]->process(message, client, id);
        return success;
    } catch (const std::exception& e) {
        return false;
    }
}
