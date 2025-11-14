/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Welcome
*/

#include "Message/Welcome.hpp"
#include "Message/Message.hpp"
#include "Client.hpp"
#include "Bytes.hpp"

#include <iostream>

Dufos::Message::Welcome::Welcome()
{
    _types = {IMessage::Type::TO_PROCESS};
}

bool Dufos::Message::Welcome::process(Network::Data::Message& message, Client& client, std::uint32_t id)
{
    std::uint32_t welcomeId = Network::Bytes::bytesToNumber(message.payload, 4);

    std::cout << "Received welcome message with ID: " << welcomeId << std::endl;
    return true;
}
