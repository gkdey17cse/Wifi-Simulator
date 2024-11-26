#include "WiFi5Simulator.hpp"
#include <iostream>
#include <iomanip> // For formatting output

WiFi5Simulator::WiFi5Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

void WiFi5Simulator::runSimulation()
{
    std::cout << "===========================================\n";
    std::cout << "     WiFi 5 Simulator - MU-MIMO Mode       \n";
    std::cout << "===========================================\n";

    int numRounds;
    std::cout << "Enter the number of rounds: ";
    std::cin >> numRounds; // User input for the number of rounds

    double currentTime = 0.0; // Simulation clock in ms
    double timeSlot = 15.0;   // Parallel communication phase duration in ms

    for (int round = 0; round < numRounds; round++) // Use user-defined number of rounds
    {
        std::cout << "\n-------------------------------------------\n";
        std::cout << "Starting Round " << round + 1 << "...\n";
        std::cout << "-------------------------------------------\n";

        // 1. Broadcast Packet
        double broadcastTime = 0.0614; // 1 KB packet transmission time
        currentTime += broadcastTime;
        std::cout << std::setw(4) << "" << "Broadcast packet transmitted at time: "
                  << std::fixed << std::setprecision(4) << currentTime << " ms\n";

        // 2. Sequential CSI Packets
        double csiTime = 0.012; // 200-byte packet transmission time
        for (int i = 0; i < numUsers; i++)
        {
            currentTime += csiTime;
            latencies.push_back(currentTime);  // Log latency for each user's CSI transmission
            timestamps.push_back(currentTime); // Log timestamp
            std::cout << std::setw(4) << "" << "User " << i
                      << " sent CSI at time: " << std::fixed << std::setprecision(4)
                      << currentTime << " ms\n";
        }

        // 3. Parallel Communication Phase
        double parallelStartTime = currentTime; // Start time for the parallel communication
        currentTime += timeSlot;                // Add 15 ms for communication
        std::cout << std::setw(4) << "" << "Parallel communication started at time: "
                  << std::fixed << std::setprecision(4) << parallelStartTime << " ms\n";

        for (int i = 0; i < numUsers; i++)
        {
            timestamps.push_back(currentTime); // Log when each user's communication completes
            std::cout << std::setw(4) << "" << "User " << i
                      << " completed communication at time: " << std::fixed << std::setprecision(4)
                      << currentTime << " ms\n";
        }
    }

    // Display metrics
    std::cout << "\n===========================================\n";
    std::cout << "               Simulation Results           \n";
    std::cout << "===========================================\n";
    std::cout << std::setw(4) << "" << "1. Throughput: "
              << std::fixed << std::setprecision(2) << calculateThroughput() << " Mbps\n";
    std::cout << std::setw(4) << "" << "2. Average Latency: "
              << std::fixed << std::setprecision(4) << calculateAverageLatency() << " ms\n";
    std::cout << std::setw(4) << "" << "3. Max Latency: "
              << std::fixed << std::setprecision(4) << calculateMaxLatency() << " ms\n";

    // Display timestamps
    std::cout << "\n===========================================\n";
    std::cout << "           Event Timestamps (ms)           \n";
    std::cout << "===========================================\n";
    for (size_t i = 0; i < timestamps.size(); i++)
    {
        std::cout << std::setw(6) << "Event " << i + 1 << ": "
                  << std::fixed << std::setprecision(4) << timestamps[i] << " ms\n";
    }
}
