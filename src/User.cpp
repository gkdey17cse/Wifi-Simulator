#include "User.hpp"

User::User(int id) : userId(id), packetsSent(0) {}

int User::getUserId() const
{
    return userId;
}

Packet User::generatePacket()
{
    return Packet(); // Default packet size of 1 KB
}

int User::getPacketsSent() const
{
    return packetsSent;
}

void User::incrementPacketsSent()
{
    packetsSent++;
}
