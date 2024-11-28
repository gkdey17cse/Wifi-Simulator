#include "WiFi6Simulator.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept> // For std::invalid_argument

WiFi6Simulator::WiFi6Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth), subChannelWidth(4) // Default to 4 MHz
{
}

double WiFi6Simulator::calculateThroughput()
{
    if (latencies.empty())
        return 0.0;

    double totalData = latencies.size() * 8192.0; // Total data in bits (1 KB = 8192 bits per packet)
    double totalTime = timestamps.back();         // Total simulation time in ms
    return (totalData / (totalTime / 1000.0)) / 1e6; // Throughput in Mbps
}

void WiFi6Simulator::runSimulation()
{
    std::cout << "===========================================\n";
    std::cout << "     WiFi 6 Simulator with OFDMA           \n";
    std::cout << "===========================================\n";

    // Ask the user for sub-channel width
    int userInputSubChannelWidth;
    std::cout << "Enter sub-channel width (2 MHz, 4 MHz, or 10 MHz): ";
    std::cin >> userInputSubChannelWidth;

    // Validate the input and throw an exception for invalid widths
    if (userInputSubChannelWidth != 2 && userInputSubChannelWidth != 4 && userInputSubChannelWidth != 10)
    {
        throw std::invalid_argument("Invalid sub-channel width! Only 2 MHz, 4 MHz, or 10 MHz are allowed.");
    }
    else
    {
        subChannelWidth = userInputSubChannelWidth;
    }

    int numSubChannels = accessPoint.getBandwidth() / subChannelWidth;

    // Calculate the data rate per sub-channel
    double dataRatePerSubChannel = (dataRate * subChannelWidth) / 20.0; // Mbps
    if (dataRatePerSubChannel <= 0)
    {
        std::cerr << "Error: Data rate per sub-channel is invalid. Exiting simulation.\n";
        return;
    }

    // Calculate transmission time for 1 KB (8192 bits) packet
    double transmissionTime = (8192.0 / (dataRatePerSubChannel * 1e6)) * 1000.0; // ms

    std::cout << "Total Bandwidth: " << accessPoint.getBandwidth() << " MHz\n";
    std::cout << "Sub-channel Width: " << subChannelWidth << " MHz\n";
    std::cout << "Number of Sub-channels: " << numSubChannels << "\n";
    std::cout << "Transmission Time per Packet: " << std::fixed << std::setprecision(4) << transmissionTime << " ms\n\n";

    latencies.clear();
    timestamps.clear();

    double currentTime = 0.0;
    int usersRemaining = numUsers;

    while (usersRemaining > 0)
    {
        std::cout << "---: Starting Frame at " << currentTime << " ms :---\n";

        int usersInThisFrame = std::min(usersRemaining, numSubChannels);
        for (int i = 0; i < usersInThisFrame; i++)
        {
            int user = numUsers - usersRemaining + i;
            double latency = currentTime + transmissionTime;

            latencies.push_back(latency);
            timestamps.push_back(latency);

            std::cout << "User " << user << " transmitted successfully on sub-channel " << i
                      << " at time " << std::fixed << std::setprecision(4) << latency << " ms.\n";
        }

        currentTime += 5.0; // Move to the next frame (frame duration is 5 ms)
        usersRemaining -= usersInThisFrame;
    }

    std::cout << "\n===============================\n";
    std::cout << "           Simulation Results           \n";
    std::cout << "===============================\n";
    std::cout << "1. Throughput: " << calculateThroughput() << " Mbps\n";
    std::cout << "2. Average Latency: " << calculateAverageLatency() << " ms\n";
    std::cout << "3. Max Latency: " << calculateMaxLatency() << " ms\n";

    std::cout << "\n---: Timestamps of successful transmissions :---\n";
    for (size_t i = 0; i < timestamps.size(); i++)
    {
        std::cout << "Event " << i + 1 << ": " << timestamps[i] << " ms\n";
    }
    std::cout << "===============================\n";
}
