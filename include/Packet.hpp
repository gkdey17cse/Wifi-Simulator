#ifndef PACKET_HPP
#define PACKET_HPP

class Packet
{
private:
    int size;                // Size of the packet in KB
    double transmissionTime; // Time taken for the packet to be transmitted

public:
    Packet(int size = 1);                  // Default size is 1 KB
    int getSize() const;                   // Getter for packet size
    void setTransmissionTime(double time); // Setter for transmission time
    double getTransmissionTime() const;    // Getter for transmission time
};

#endif
