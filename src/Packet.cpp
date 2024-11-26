#include "Packet.hpp"

Packet::Packet(int size) : size(size), transmissionTime(0.0) {}

int Packet::getSize() const
{
    return size;
}

void Packet::setTransmissionTime(double time)
{
    transmissionTime = time;
}

double Packet::getTransmissionTime() const
{
    return transmissionTime;
}
