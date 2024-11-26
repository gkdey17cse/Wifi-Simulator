#ifndef ACCESS_POINT_HPP
#define ACCESS_POINT_HPP

#include <vector>
#include "User.hpp"
#include "Channel.hpp"

class AccessPoint
{
private:
    int numUsers;            // Number of users connected
    Channel channel;         // Communication channel
    std::vector<User> users; // List of users

public:
    AccessPoint(int numUsers, int bandwidth); // Constructor to initialize AP
    void addUser(const User &user);           // Adds a user to the AP
    void manageCommunication();               // Simulates communication between users and AP
    bool sniffChannel();
    void occupyChannel();
    void releaseChannel();
    int getBandwidth() const;
};

#endif
