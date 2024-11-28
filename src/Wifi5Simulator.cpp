#include "WiFi5Simulator.hpp"
#include <iostream>
#include <iomanip> // For formatting output
#include <numeric> // For accumulate
#include <algorithm> // For max_element

WiFi5Simulator::WiFi5Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

void WiFi5Simulator::runSimulation()
{
    std::cout << "===========================================\n";
    std::cout << "     WiFi 5 Simulator - MU-MIMO Mode       \n";
    std::cout << "===========================================\n";

    int numPacketsPerUser;
    std::cout << "Enter the number of packets each user wants to send: ";
    std::cin >> numPacketsPerUser;

    double currentTime = 0.0; // Simulation clock in ms
    double timeSlot = 15.0;   // Parallel communication phase duration in ms
    double broadcastTime = 0.0614; // 1 KB packet transmission time
    double csiTime = 0.012;        // 200-byte packet transmission time for CSI
    double packetTransmissionTime = 0.0614; // Time to send one data packet

    int totalPackets = numPacketsPerUser * numUsers;
    int packetsSent = 0; // Track the total number of packets sent

    std::vector<int> userPackets(numUsers, 0); // Track packets sent by each user

    while (packetsSent < totalPackets)
    {
        std::cout << "\n-------------------------------------------\n";
        std::cout << "Starting Round...\n";
        std::cout << "-------------------------------------------\n";

        // 1. Broadcast Packet
        currentTime += broadcastTime;
        std::cout << std::setw(4) << "" << "Broadcast packet transmitted at time: "
                  << std::fixed << std::setprecision(4) << currentTime << " ms\n";

        // 2. Sequential CSI Packets
        for (int i = 0; i < numUsers; i++)
        {
            currentTime += csiTime;
            std::cout << std::setw(4) << "" << "User " << i
                      << " sent CSI at time: " << std::fixed << std::setprecision(4)
                      << currentTime << " ms\n";
        }

        // 3. Round-Robin Data Transmission
        double parallelStartTime = currentTime; // Start time for the parallel communication
        double timeSlotEnd = parallelStartTime + timeSlot; // End of the current time slot
        bool slotExhausted = false; // Flag to track time slot exhaustion

        std::cout << std::setw(4) << "" << "Parallel communication started at time: "
                  << std::fixed << std::setprecision(4) << parallelStartTime << " ms\n";

        for (int i = 0; i < numUsers && !slotExhausted; i++)
        {
            while (userPackets[i] < numPacketsPerUser && packetsSent < totalPackets)
            {
                double transmissionEndTime = currentTime + packetTransmissionTime;

                // Check if the current transmission exceeds the 15 ms time slot
                if (transmissionEndTime > timeSlotEnd)
                {
                    std::cout << "Time slot exhausted. Ending round.\n";
                    slotExhausted = true;
                    break;
                }

                userPackets[i]++;
                packetsSent++;
                currentTime = transmissionEndTime; // Update current time to the end of this transmission
                latencies.push_back(currentTime);  // Log latency for each packet
                timestamps.push_back(currentTime); // Log timestamp
                std::cout << std::setw(4) << "" << "User " << i
                          << " transmitted successfully at time: " << std::fixed << std::setprecision(4)
                          << currentTime << " ms\n";
            }

            // If the time slot is exhausted, break out of the user loop as well
            if (slotExhausted)
            {
                break;
            }
        }
    }

    // Display metrics
    std::cout << "\n===========================================\n";
    std::cout << "               Simulation Results           \n";
    std::cout << "===========================================\n";
    std::cout << std::setw(4) << "" << "1. Throughput: "
              << std::fixed << std::setprecision(2) << calculateThroughput(totalPackets, currentTime) << " Mbps\n";
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

// Helper Functions for Metrics
double WiFi5Simulator::calculateThroughput(int totalPackets, double totalTime)
{
    double totalData = totalPackets * 1.0; // 1 KB per packet
    return (totalData * 8.0) / (totalTime / 1.0); // Convert ms to seconds for Mbps
}

double WiFi5Simulator::calculateAverageLatency()
{
    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    return totalLatency / latencies.size();
}

double WiFi5Simulator::calculateMaxLatency()
{
    return *std::max_element(latencies.begin(), latencies.end());
}
