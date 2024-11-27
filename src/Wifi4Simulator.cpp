#include "WiFi4Simulator.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <map>
#include <vector>
#include <functional>

// Define the constructor
WiFi4Simulator::WiFi4Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

double WiFi4Simulator::calculateThroughput()
{
    if (timestamps.empty())
        return 0.0;

    double totalData = timestamps.size() * 8192;                  // Total data in bits
    double totalTime = timestamps.back() / 1000.0;                // Total time in seconds
    return (totalTime > 0) ? (totalData / totalTime) / 1e6 : 0.0; // Throughput in Mbps
}

void WiFi4Simulator::runSimulation()
{
    std::cout << "WiFi 4 Simulator: CSMA/CA Protocol Simulation\n";
    std::cout << "All users arrive at t = 0 ms.\n";
    std::cout << "--------------------------------------------------\n";

    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random backoff times

    // Clear previous simulation data
    latencies.clear();
    timestamps.clear();

    double currentTime = 0.0;         // Simulation clock in ms
    double transmissionTime = 0.0614; // Transmission time for a 1 KB packet (based on 133.33 Mbps)

    // Map to track backoff times for users
    std::map<int, double> userBackoffMap;

    // Initialize backoff times for all users
    for (int i = 0; i < numUsers; i++)
    {
        double backoffTime = (i == 0) ? 0.0 : (rand() % 10 + 1); // User 0 has no backoff
        userBackoffMap[i] = backoffTime;
        std::cout << "User " << i << " assigned backoff time: " << backoffTime << " ms.\n";
    }

    std::cout << "--------------------------------------------------\n";

    // Process users until all have transmitted successfully
    while (!userBackoffMap.empty())
    {
        // Find the minimum backoff time
        double minBackoffTime = std::numeric_limits<double>::max();
        for (const auto &[userId, backoffTime] : userBackoffMap)
        {
            minBackoffTime = std::min(minBackoffTime, backoffTime);
        }

        // Identify users with the minimum backoff time
        std::vector<int> usersWithMinBackoff;
        for (const auto &[userId, backoffTime] : userBackoffMap)
        {
            if (backoffTime == minBackoffTime)
                usersWithMinBackoff.push_back(userId);
        }

        if (usersWithMinBackoff.size() > 1)
        {
            // Collision detected
            std::cout << "Collision detected! Users ";
            for (size_t i = 0; i < usersWithMinBackoff.size(); ++i)
            {
                std::cout << usersWithMinBackoff[i];
                if (i < usersWithMinBackoff.size() - 1)
                    std::cout << ", ";
            }
            std::cout << " have the same backoff time: " << minBackoffTime << " ms.\n";

            // Transmit for the first user
            int transmittingUser = usersWithMinBackoff[0];
            currentTime = std::max(currentTime, minBackoffTime);
            std::cout << "User " << transmittingUser << " transmitted successfully at time " << currentTime << " ms.\n";

            currentTime += transmissionTime;
            latencies.push_back(currentTime);
            timestamps.push_back(currentTime);

            // Retry for remaining users
            for (size_t i = 1; i < usersWithMinBackoff.size(); ++i)
            {
                int retryUser = usersWithMinBackoff[i];
                double newBackoff = currentTime + (rand() % 10 + 1);
                userBackoffMap[retryUser] = newBackoff;
                std::cout << "User " << retryUser << " retries with new backoff time: " << newBackoff << " ms.\n";
            }

            // Remove the transmitting user
            userBackoffMap.erase(transmittingUser);
        }
        else
        {
            // Single user transmission
            int user = usersWithMinBackoff[0];
            currentTime = std::max(currentTime, minBackoffTime);
            std::cout << "User " << user << " transmitted successfully at time " << currentTime << " ms.\n";

            currentTime += transmissionTime;
            latencies.push_back(currentTime);
            timestamps.push_back(currentTime);

            // Remove the transmitting user
            userBackoffMap.erase(user);
        }
    }

    // Calculate metrics
    std::cout << "\nSimulation Results:\n";
    std::cout << "1. Throughput: " << calculateThroughput() << " Mbps\n";
    std::cout << "2. Average Latency: " << calculateAverageLatency() << " ms\n";
    std::cout << "3. Max Latency: " << calculateMaxLatency() << " ms\n";

    // Display timestamps
    std::cout << "\nTimestamps of successful transmissions:\n";
    std::cout << "{ ";
    for (const auto &timestamp : timestamps)
    {
        std::cout << "| " << timestamp << " ms | ";
    }
    std::cout << " }\n";
}
