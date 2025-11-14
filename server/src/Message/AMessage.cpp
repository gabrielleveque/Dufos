/*
** EPITECH PROJECT, 2025
** dufos
** File description:
** AMessage
*/

#include "Message/AMessage.hpp"
#include "Bytes.hpp"

std::set<Dufos::Message::AMessage::Type> Dufos::Message::AMessage::getType() const
{
    return _types;
}

bool Dufos::Message::AMessage::execute(Server& server, std::uint32_t id)
{
    (void) server;
    (void) id;
    return false;
}

bool Dufos::Message::AMessage::process(Network::Data::Message& message, Server& server, std::uint32_t id)
{
    (void) message;
    (void) server;
    (void) id;
    return false;
}

void Dufos::Message::AMessage::setMessageSize(std::vector<std::uint8_t>& msg, std::uint32_t size)
{
    std::vector<std::uint8_t> sizeBytes = Network::Bytes::numberToBytes(size, 4);

    msg.insert(msg.end(), sizeBytes.begin(), sizeBytes.end());
}
