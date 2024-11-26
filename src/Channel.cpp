#include "Channel.hpp"

Channel::Channel(int bandwidth) : bandwidth(bandwidth), isBusy(false) {}

bool Channel::sniffChannel()
{
    // Simulate channel state (50% chance of being busy)
    return !isBusy && (rand() % 2 == 0);
}

void Channel::occupyChannel()
{
    isBusy = true;
}

void Channel::releaseChannel()
{
    isBusy = false;
}

int Channel::getBandwidth() const
{
    return bandwidth;
}
