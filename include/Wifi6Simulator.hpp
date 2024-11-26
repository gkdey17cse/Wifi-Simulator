#ifndef WIFI6SIMULATOR_HPP
#define WIFI6SIMULATOR_HPP

#include "Simulator.hpp"

class WiFi6Simulator : public Simulator
{
public:
    WiFi6Simulator(int numUsers, int bandwidth);
    void runSimulation() override;
    double calculateThroughput() override;

private:
    int subChannelWidth; // Sub-channel width in MHz
};

#endif
