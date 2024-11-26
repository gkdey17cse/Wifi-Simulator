#ifndef WIFI4SIMULATOR_HPP
#define WIFI4SIMULATOR_HPP

#include "Simulator.hpp"

class WiFi4Simulator : public Simulator
{
public:
    WiFi4Simulator(int numUsers, int bandwidth);
    void runSimulation() override;
    double calculateThroughput() override; // Correct declaration with override keyword
};

#endif
