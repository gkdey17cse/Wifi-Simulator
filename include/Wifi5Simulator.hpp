#ifndef WIFI5SIMULATOR_HPP
#define WIFI5SIMULATOR_HPP

#include "Simulator.hpp"

class WiFi5Simulator : public Simulator
{
public:
    WiFi5Simulator(int numUsers, int bandwidth);
    void runSimulation() override;
};

#endif
