#include "Simulator.hpp"

Simulator::Simulator(int numUsers, int bandwidth)
    : accessPoint(numUsers, bandwidth), numUsers(numUsers) {}

double Simulator::calculateThroughput()
{
    if (timestamps.empty())
        return 0.0;

    double totalData = timestamps.size() * 8192.0;      // Total data in bits (1 KB = 8192 bits per packet)
    double totalTime = timestamps.back() / 1000.0;     // Convert ms to seconds
    return (totalTime > 0) ? (totalData / totalTime) / 1e6 : 0.0; // Throughput in Mbps
}


double Simulator::calculateAverageLatency()
{
    if (latencies.empty())
        return 0.0; // Avoid division by zero

    double totalLatency = 0;
    for (const auto &latency : latencies)
    {
        totalLatency += latency;
    }
    return totalLatency / latencies.size(); // Average latency in ms
}

double Simulator::calculateMaxLatency()
{
    if (latencies.empty())
        return 0.0;

    double maxLatency = 0;
    for (const auto &latency : latencies)
    {
        if (latency > maxLatency)
        {
            maxLatency = latency;
        }
    }
    return maxLatency; // Maximum latency in ms
}
