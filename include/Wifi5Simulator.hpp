#ifndef WIFI5SIMULATOR_HPP
#define WIFI5SIMULATOR_HPP

#include "Simulator.hpp"
#include <vector>

class WiFi5Simulator : public Simulator
{
public:
    WiFi5Simulator(int numUsers, int bandwidth);
    void runSimulation() override;
    
    using Simulator::calculateThroughput; // Allow access to base class method

    double calculateThroughput(int totalPackets, double totalTime); // Declare custom throughput method
    double calculateAverageLatency(); // Declare custom average latency
    double calculateMaxLatency();     // Declare custom max latency
};

#endif
