#include "AccessPoint.hpp"
#include <iostream>
using namespace std;

AccessPoint::AccessPoint(int numUsers, int bandwidth) : numUsers(numUsers), channel(bandwidth) {}

void AccessPoint::addUser(const User &user)
{
    users.push_back(user);
}

bool AccessPoint::sniffChannel()
{
    return channel.sniffChannel();
}

void AccessPoint::occupyChannel()
{
    channel.occupyChannel();
}

void AccessPoint::releaseChannel()
{
    channel.releaseChannel();
}

int AccessPoint::getBandwidth() const
{
    return channel.getBandwidth();
}

void AccessPoint::manageCommunication()
{
    for (auto &user : users)
    {
        bool success = false;
        while (!success)
        {
            if (channel.sniffChannel())
            {
                channel.occupyChannel();
                Packet packet = user.generatePacket();
                cout << "User " << user.getUserId() << " transmitted a packet of size "
                     << packet.getSize() << " KB.\n";
                user.incrementPacketsSent();
                success = true;
                channel.releaseChannel();
            }
            else
            {
                int backoffTime = rand() % 10 + 1; // Random backoff between 1-10 ms
                cout << "User " << user.getUserId() << " backs off for " << backoffTime << " ms.\n";
            }
        }
    }
}
