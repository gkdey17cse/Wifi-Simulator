#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <random>

class Channel
{
private:
    int bandwidth; // Bandwidth of the channel in MHz
    bool isBusy;   // Indicates if the channel is currently busy

public:
    Channel(int bandwidth);   // Constructor to initialize bandwidth
    bool sniffChannel();      // Checks if the channel is free
    void occupyChannel();     // Marks the channel as busy
    void releaseChannel();    // Marks the channel as free
    int getBandwidth() const; // Getter for channel bandwidth

};

#endif
