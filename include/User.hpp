#ifndef USER_HPP
#define USER_HPP

#include "Packet.hpp"

class User
{
private:
    int userId;      // Unique identifier for the user
    int packetsSent; // Counter for packets sent by the user

public:
    User(int id);                // Constructor to initialize user ID
    int getUserId() const;       // Getter for user ID
    Packet generatePacket();     // Generates a new packet for transmission
    int getPacketsSent() const;  // Getter for the number of packets sent
    void incrementPacketsSent(); // Increments the packets sent count
};

#endif
