#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "AccessPoint.hpp"
#include <vector>

class Simulator
{
protected:
    AccessPoint accessPoint;
    int numUsers;
    std::vector<double> latencies;
    std::vector<double> timestamps;

    const double dataRate = 133.33; // Mbps (256-QAM with coding rate 5/6)

public:
    Simulator(int numUsers, int bandwidth);

    virtual void runSimulation() = 0; 
    virtual double calculateThroughput();

    double calculateAverageLatency();
    double calculateMaxLatency();

    virtual ~Simulator() = default;
};

#endif
