#include "WiFi4Simulator.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>
#include <functional>

// Define the constructor
WiFi4Simulator::WiFi4Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

double WiFi4Simulator::calculateThroughput()
{
    if (timestamps.empty())
        return 0.0;

    double totalData = timestamps.size() * 8192;      // Total data in bits
    double totalTime = timestamps.back() / 1000.0;   // Total time in seconds
    return (totalTime > 0) ? (totalData / totalTime) / 1e6 : 0.0; // Throughput in Mbps
}


void WiFi4Simulator::runSimulation()
{
    std::cout << "===========================================\n";
    std::cout << "     WiFi 4 Simulator with CSMA/CA      \n";
    std::cout << "===========================================\n";

    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random backoff times

    // Clear previous simulation data
    latencies.clear();
    timestamps.clear();

    double currentTime = 0.0;         // Simulation clock in ms
    double transmissionTime = 0.0614; // Transmission time for a 1 KB packet (based on 133.33 Mbps)

    // Priority queue to manage users based on their backoff times
    using UserBackoff = std::pair<double, int>; // Pair of <backoff time, user ID>
    std::priority_queue<UserBackoff, std::vector<UserBackoff>, std::greater<>> backoffQueue;

    // Initialize backoff times for all users
    for (int i = 0; i < numUsers; i++)
    {
        double initialBackoff = (i == 0) ? 0.0 : (rand() % 10 + 1); // User 0 has no backoff
        backoffQueue.push({initialBackoff, i});
    }

    // Process users
    while (!backoffQueue.empty())
    {
        auto [backoffTime, user] = backoffQueue.top();
        backoffQueue.pop();

        if (currentTime < backoffTime)
        {
            // Wait until the backoff time
            std::cout << "User " << user << " waiting with backoff time: " << backoffTime
                      << " ms. Current time: " << currentTime << " ms.\n";
            currentTime = backoffTime;
        }

        // Transmit data
        currentTime += transmissionTime;
        latencies.push_back(currentTime);  // Log latency
        timestamps.push_back(currentTime); // Log successful transmission time
        std::cout << "User " << user << " transmitted successfully at time " << currentTime << " ms.\n";
    }

    // Calculate metrics
    std::cout << "\n===============================\n";
    std::cout << "           Simulation Results           \n";
    std::cout << "===============================\n";
    std::cout << "1. Throughput: " << calculateThroughput() << " Mbps\n";
    std::cout << "2. Average Latency: " << calculateAverageLatency() << " ms\n";
    std::cout << "3. Max Latency: " << calculateMaxLatency() << " ms\n";

    // Display timestamps
    std::cout << "\n---: Timestamps of successful transmissions :---\n";
    int userIndex = 0;
    for (const auto &timestamp : timestamps) // Range-based loop
    {
        std::cout << "User " << userIndex++ << ": " << timestamp << " ms\n";
    }
    std::cout << "===============================\n";
}
